#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 100
#define HASH_LENGTH 64

void hash_password(const char *password, unsigned char output[HASH_LENGTH + 1]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf((char *)output + i * 2, "%02x", hash[i]);
    }
    output[HASH_LENGTH] = '\0';
}

void insert_into_database(const char *username, const char *hashed_password) {
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, hashed_password);
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_USERNAME_LENGTH + 1];
    unsigned char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    if (scanf("%100s", username) != 1) {
        fprintf(stderr, "Error reading username.\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (scanf("%100s", password) != 1) {
        fprintf(stderr, "Error reading password.\n");
        return EXIT_FAILURE;
    }

    hash_password(password, hashed_password);
    insert_into_database(username, (const char *)hashed_password);

    return EXIT_SUCCESS;
}