#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 256
#define PASSWORD_MAX 256
#define HASH_LENGTH 64

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

int insert_user(const char *username, const char *hashed_password) {
    // Dummy function to simulate database insertion
    printf("Inserting user: %s with hashed password: %s\n", username, hashed_password);
    return 1; // Return 1 for success, 0 for failure
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    if (fgets(username, USERNAME_MAX, stdin) == NULL || strlen(username) <= 1) {
        fprintf(stderr, "Invalid username.\n");
        return 1;
    }
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    if (fgets(password, PASSWORD_MAX, stdin) == NULL || strlen(password) <= 1) {
        fprintf(stderr, "Invalid password.\n");
        return 1;
    }
    password[strcspn(password, "\n")] = 0; // Remove newline

    hash_password(password, hashed_password);
    if (insert_user(username, hashed_password)) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
    }

    return 0;
}