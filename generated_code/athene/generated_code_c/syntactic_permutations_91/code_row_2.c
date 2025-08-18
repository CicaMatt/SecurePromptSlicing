#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USER 256
#define MAX_PASS 1024

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int save_user(const char *username, const unsigned char *hashed_password) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return 0;
    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");
    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (scanf("%255s", username) != 1) {
        return 1;
    }

    printf("Enter password: ");
    if (scanf("%1023s", password) != 1) {
        return 1;
    }

    hash_password(password, hashed_password);
    if (!save_user(username, hashed_password)) {
        fprintf(stderr, "Failed to save user.\n");
        return 1;
    }

    printf("User registered successfully.\n");
    return 0;
}