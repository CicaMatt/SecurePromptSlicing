#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Update(&ctx, salt, SALT_LENGTH);
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
    strcpy(hashed + (SHA256_DIGEST_LENGTH * 2), salt);
}

int main() {
    char username[100], password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Simulate storing in a database
    printf("Storing user information:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);

    return 0;
}