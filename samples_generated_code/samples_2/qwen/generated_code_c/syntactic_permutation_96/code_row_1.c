#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char hash[HASH_SIZE]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_user(const char *username, const unsigned char hash[HASH_SIZE]) {
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:", username);
    for (int i = 0; i < HASH_SIZE; i++) {
        fprintf(db, "%02x", hash[i]);
    }
    fprintf(db, "\n");
    fclose(db);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    unsigned char hash[HASH_SIZE];

    printf("Enter your username: ");
    if (fgets(username, USERNAME_MAX, stdin) != NULL) {
        username[strcspn(username, "\n")] = 0; // Remove newline character
    }

    printf("Enter your password: ");
    if (fgets(password, PASSWORD_MAX, stdin) != NULL) {
        password[strcspn(password, "\n")] = 0; // Remove newline character
    }

    hash_password(password, hash);
    store_user(username, hash);

    printf("User registered successfully.\n");

    return 0;
}