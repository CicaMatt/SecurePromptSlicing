#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USER 100
#define MAX_PASS 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_user(const char *username, const unsigned char *password_hash) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return 0;

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", password_hash[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hash);

    if (save_user(username, hash)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}