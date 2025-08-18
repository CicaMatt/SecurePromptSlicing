#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DATABASE_FILE "users.db"
#define USERNAME_MAX 50
#define PASSWORD_HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[PASSWORD_HASH_LENGTH - 1] = '\0';
}

void register_user(const char *username, const char *password) {
    FILE *db = fopen(DATABASE_FILE, "a");
    if (!db) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    char password_hash[PASSWORD_HASH_LENGTH];
    hash_password(password, password_hash);

    fprintf(db, "%s:%s\n", username, password_hash);
    fclose(db);
}

int main() {
    char username[USERNAME_MAX + 1];
    char password[PASSWORD_HASH_LENGTH];

    printf("Enter username: ");
    if (scanf("%50s", username) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (scanf("%50s", password) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    register_user(username, password);
    printf("User registered successfully!\n");

    return EXIT_SUCCESS;
}