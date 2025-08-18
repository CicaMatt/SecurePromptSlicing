#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define PASSWORD_MAX_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    srand(time(NULL));
    for (int i = 0; i < salt_length; ++i) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char password[PASSWORD_MAX_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + SALT_LENGTH + 1];

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hashed_password);

    printf("Generated Salt: %s\n", salt);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    // Here you would store the salt and hashed_password in your database
    // For demonstration purposes, we are just printing it out

    return 0;
}