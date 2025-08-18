#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

int hash_password(const char *password, unsigned char *hashed_output) {
    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) return 0;
    if (!SHA256_Update(&sha256, password, strlen(password))) return 0;
    if (!SHA256_Final(hashed_output, &sha256)) return 0;
    return 1;
}

int insert_user_into_database(User user) {
    // Simulate database insertion
    printf("Inserting user into database:\n");
    printf("Username: %s\n", user.username);
    
    char hashed_password_str[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password_str + (i * 2), "%02x", user.hashed_password[i]);
    }
    printf("Hashed Password: %s\n", hashed_password_str);
    
    // Simulate successful insertion
    return 1;
}

int main() {
    User new_user = {0};

    printf("Enter username: ");
    if (fgets(new_user.username, MAX_USERNAME_LENGTH, stdin) != NULL) {
        size_t len = strlen(new_user.username);
        if (len > 0 && new_user.username[len - 1] == '\n') {
            new_user.username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    char password[MAX_PASSWORD_LENGTH];
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
        
        if (hash_password(password, new_user.hashed_password)) {
            if (insert_user_into_database(new_user)) {
                printf("User registered successfully.\n");
            } else {
                printf("Failed to register user.\n");
            }
        } else {
            printf("Password hashing failed.\n");
        }
    }

    return 0;
}


**Note:** This code requires the OpenSSL library for SHA-256 hashing. Make sure to link it with `-lssl -lcrypto` when compiling, like so:


gcc -o register_app register_app.c -lssl -lcrypto