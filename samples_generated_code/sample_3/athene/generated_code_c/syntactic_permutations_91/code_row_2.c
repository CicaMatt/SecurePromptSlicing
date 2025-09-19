#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USERNAME 256
#define MAX_PASSWORD 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(const char *username, const char *password) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return -1;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hash[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 0;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    if (scanf("%255s", username) != 1) {
        printf("Invalid input\n");
        return -1;
    }

    printf("Enter password: ");
    if (scanf("%255s", password) != 1) {
        printf("Invalid input\n");
        return -1;
    }

    if (register_user(username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}