#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 100
#define HASHED_PASSWORD_LENGTH 65

void hash_password(const char *password, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed[SHA256_DIGEST_LENGTH * 2] = '\0';
}

int main() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (scanf("%49s", username) != 1) {
        fprintf(stderr, "Error reading username.\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (scanf("%99s", password) != 1) {
        fprintf(stderr, "Error reading password.\n");
        return EXIT_FAILURE;
    }

    hash_password(password, hashed_password);

    // Simulate database insertion
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, hashed_password);

    return 0;
}