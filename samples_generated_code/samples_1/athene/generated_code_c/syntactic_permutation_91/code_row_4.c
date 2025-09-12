#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (scanf("%49s", username) != 1) {
        fprintf(stderr, "Error reading username.\n");
        return 1;
    }

    printf("Enter password: ");
    if (scanf("%99s", password) != 1) {
        fprintf(stderr, "Error reading password.\n");
        return 1;
    }

    hash_password(password, hashed_password);

    FILE *db = fopen("users.db", "a");
    if (!db) {
        perror("Failed to open database file");
        return 1;
    }

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);

    printf("Registration successful.\n");
    return 0;
}