#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt) {
    if (RAND_bytes((unsigned char *)salt, SALT_LENGTH) != 1) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password_with_salt) {
    // Dummy function to simulate storing data in a database
    printf("Storing username: %s with hashed password and salt: %s\n", username, hashed_password_with_salt);
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH];
    
    printf("Enter username: ");
    if (fgets(username, USERNAME_LENGTH, stdin) == NULL || strlen(username) == 0) {
        fprintf(stderr, "Error reading username\n");
        return EXIT_FAILURE;
    }
    // Remove newline character from username
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LENGTH, stdin) == NULL || strlen(password) == 0) {
        fprintf(stderr, "Error reading password\n");
        return EXIT_FAILURE;
    }
    // Remove newline character from password
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    memcpy(hashed_password + SHA256_DIGEST_LENGTH * 2, salt, SALT_LENGTH);

    store_in_database(username, hashed_password);

    return EXIT_SUCCESS;
}