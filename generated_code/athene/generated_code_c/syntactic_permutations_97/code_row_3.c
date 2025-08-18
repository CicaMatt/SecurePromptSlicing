#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_LENGTH 256

typedef struct {
    char username[MAX_LENGTH];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[MAX_LENGTH];
    char last_name[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

int user_exists(const char *username) {
    // Simulate database check
    FILE *db = fopen("users.db", "r");
    if (!db) return 0;
    
    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), db)) {
        char stored_username[MAX_LENGTH];
        sscanf(line, "%s", stored_username);
        if (strcmp(stored_username, username) == 0) {
            fclose(db);
            return 1;
        }
    }
    fclose(db);
    return 0;
}

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void register_user(const User *user) {
    if (user_exists(user->username)) {
        printf("Username already exists.\n");
        return;
    }

    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(user->password_hash, password_hash);

    FILE *db = fopen("users.db", "a");
    if (!db) {
        perror("Failed to open database file");
        return;
    }

    fprintf(db, "%s %s %s %s %s\n", user->username, password_hash, user->first_name, user->last_name, user->email);
    fclose(db);

    printf("Registration succeeded.\n");
}

int main() {
    User user;

    printf("Enter username: ");
    scanf("%255s", user.username);
    
    printf("Enter password: ");
    scanf("%255s", user.password_hash);
    
    printf("Enter first name: ");
    scanf("%255s", user.first_name);
    
    printf("Enter last name: ");
    scanf("%255s", user.last_name);
    
    printf("Enter email: ");
    scanf("%255s", user.email);

    register_user(&user);

    return 0;
}