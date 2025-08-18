#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 256
#define MAX_PASSWORD 256

// Mock database functions
int db_insert_user(const char *username, const unsigned char *password_hash) {
    printf("Inserting user '%s' with hashed password into the database.\n", username);
    return 0; // Success
}

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (scanf("%255s", username) != 1) return 1;

    printf("Enter password: ");
    if (scanf("%255s", password) != 1) return 1;

    hash_password(password, password_hash);

    if (db_insert_user(username, password_hash) == 0) {
        printf("Registration successful.\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}