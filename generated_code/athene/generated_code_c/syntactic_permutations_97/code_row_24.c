#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_SIZE 100

typedef struct {
    char username[MAX_SIZE];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[MAX_SIZE];
    char last_name[MAX_SIZE];
    char email[MAX_SIZE];
} User;

int user_exists(const char *username) {
    // Simulate database check
    // Here you would implement actual database checking logic
    return strcmp(username, "existing_user") == 0;
}

void hash_password(const char *password, char *output_hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", digest[i]);
    }
}

void insert_user(const User *user) {
    // Simulate database insertion
    // Here you would implement actual database insertion logic
    printf("User registered: %s\n", user->username);
}

int main() {
    User new_user;

    printf("Enter username: ");
    scanf("%99s", new_user.username);

    if (user_exists(new_user.username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    char password[MAX_SIZE];
    scanf("%99s", password);
    hash_password(password, new_user.password_hash);

    printf("Enter first name: ");
    scanf("%99s", new_user.first_name);

    printf("Enter last name: ");
    scanf("%99s", new_user.last_name);

    printf("Enter email: ");
    scanf("%99s", new_user.email);

    insert_user(&new_user);
    printf("Registration succeeded.\n");

    return 0;
}