#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

typedef struct {
    char *username;
    char *password_hash;
} User;

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    const int MAX_USERNAME_LENGTH = 100;
    const int MAX_PASSWORD_LENGTH = 100;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);

    // Simulate database insertion
    User user;
    user.username = strdup(username);
    char *hex_password_hash = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_password_hash + (i * 2), "%02x", password_hash[i]);
    }
    user.password_hash = hex_password_hash;

    printf("User registered successfully:\n");
    printf("Username: %s\n", user.username);
    printf("Password Hash: %s\n", user.password_hash);

    free(user.username);
    free(user.password_hash);

    return 0;
}