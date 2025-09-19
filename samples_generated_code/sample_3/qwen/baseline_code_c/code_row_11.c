#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    srand(time(NULL));
    for (size_t i = 0; i < salt_length; i++) {
        salt[i] = 'A' + rand() % ('z' - 'A');
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salted_password[MAX_PASSWORD + SALT_LENGTH + 1];

    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i * 2], "%02x", hash[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void store_in_database(const char *username, const char *salted_hash) {
    // This function would typically contain code to insert the username and salted_hash into a database.
    // For demonstration purposes, we'll just print it out.
    printf("Storing in database:\nUsername: %s\nSalted Hash: %s\n", username, salted_hash);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char salted_hash[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    snprintf(salted_hash, sizeof(salted_hash), "%s%s", hashed_password, salt);
    store_in_database(username, salted_hash);

    return 0;
}