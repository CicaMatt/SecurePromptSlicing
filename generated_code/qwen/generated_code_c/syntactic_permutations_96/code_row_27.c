#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < salt_length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[PASSWORD_MAX_LENGTH + SALT_LENGTH + 1];

    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_output + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + 1];

    printf("Enter username: ");
    if (scanf("%s", username) != 1) {
        fprintf(stderr, "Error reading username.\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (scanf("%s", password) != 1) {
        fprintf(stderr, "Error reading password.\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hashed_password);

    // Simulate storing in a database
    printf("Stored Username: %s\n", username);
    printf("Stored Salt: %s\n", salt);
    printf("Stored Hashed Password: %s\n", hashed_password);

    return EXIT_SUCCESS;
}