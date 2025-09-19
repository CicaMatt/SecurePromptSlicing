#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define HASH_SIZE 32

void hash_password(const char *password, unsigned char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf((char *)output + (i * 2), "%02x", hash[i]);
    }
}

void register_user(const char *username, const char *password) {
    unsigned char hashed_password[HASH_SIZE + 1];
    memset(hashed_password, 0, HASH_SIZE + 1);
    hash_password(password, hashed_password);

    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);
}

int main() {
    char username[USERNAME_MAX_LENGTH + 1];
    char password[PASSWORD_MAX_LENGTH + 1];

    printf("Enter username: ");
    if (scanf("%50s", username) != 1) {
        fprintf(stderr, "Error reading username\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (scanf("%50s", password) != 1) {
        fprintf(stderr, "Error reading password\n");
        return EXIT_FAILURE;
    }

    register_user(username, password);
    printf("User registered successfully.\n");

    return EXIT_SUCCESS;
}