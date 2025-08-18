#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USER 100
#define DB_FILE "users.db"

typedef struct {
    char username[50];
    char password_hash[65];
    char first_name[50];
    char last_name[50];
    char email[100];
} User;

int user_exists(const char *username) {
    FILE *file = fopen(DB_FILE, "r");
    if (file == NULL) return 0;
    
    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void hash_password(const char *password, char *output_hash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }
    output_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    User new_user;
    strcpy(new_user.username, username);
    hash_password(password, new_user.password_hash);
    strcpy(new_user.first_name, first_name);
    strcpy(new_user.last_name, last_name);
    strcpy(new_user.email, email);

    FILE *file = fopen(DB_FILE, "a");
    if (file == NULL) {
        printf("Failed to open database file.\n");
        return;
    }
    fwrite(&new_user, sizeof(User), 1, file);
    fclose(file);
    printf("Registration succeeded.\n");
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password, first_name, last_name, email);
    
    return 0;
}