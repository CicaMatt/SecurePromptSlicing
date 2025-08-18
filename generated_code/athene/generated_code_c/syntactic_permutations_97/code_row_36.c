#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_SIZE 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_SIZE];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (db == NULL) return 0;
    
    User user;
    while (fscanf(db, "%s %s", user.username, user.password_hash) != EOF) {
        if (strcmp(user.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }
    fclose(db);
    return 0;
}

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void register_user(const char *username, const char *password_hash, const char *first_name, const char *last_name, const char *email) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        printf("Failed to open database file.\n");
        return;
    }
    
    fprintf(db, "%s %s\n", username, password_hash);
    fclose(db);

    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_SIZE], password[MAX_SIZE], first_name[MAX_SIZE], last_name[MAX_SIZE], email[MAX_SIZE];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%s", username);
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%s", password);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    hash_password(password, password_hash);
    register_user(username, password_hash, first_name, last_name, email);

    return 0;
}