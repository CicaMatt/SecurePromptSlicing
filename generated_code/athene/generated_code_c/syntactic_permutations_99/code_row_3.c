#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int insert_into_database(const char *username, const unsigned char *hash) {
    // Placeholder for database insertion logic
    printf("Inserting username: %s and hashed password into the database.\n", username);
    return 1; // Return 1 for success, modify as needed for actual DB interaction
}

int main() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    unsigned char hash[HASH_SIZE];

    printf("Enter username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_SIZE, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hash);

    if (insert_into_database(username, hash)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}