#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

int register_user(const char *username, const char *password) {
    char hashed_password[HASH_LENGTH];
    hash_password(password, hashed_password);

    // Simulate database insertion
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, hashed_password);
    return 0; // Assuming success for simplicity
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    if (register_user(username, password) == 0) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}