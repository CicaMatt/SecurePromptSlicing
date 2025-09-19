#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 256
#define MAX_PASSWORD 256
#define DB_FILE "users.db"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_user(const char *username, const unsigned char *hashed_password) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) return 0;

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    if (fgets(username, MAX_USERNAME, stdin) == NULL || strlen(username) <= 1) {
        return 1;
    }
    username[strcspn(username, "\n")] = 0;

    printf("Enter your password: ");
    if (fgets(password, MAX_PASSWORD, stdin) == NULL || strlen(password) <= 1) {
        return 1;
    }
    password[strcspn(password, "\n")] = 0;

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    if (save_user(username, hashed_password)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}