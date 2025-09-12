#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define DATABASE_FILE "users.db"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(const char *username, const char *password) {
    FILE *db = fopen(DATABASE_FILE, "a");
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
    char username[100], password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    if (register_user(username, password) == 0) {
        printf("Registration successful.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}