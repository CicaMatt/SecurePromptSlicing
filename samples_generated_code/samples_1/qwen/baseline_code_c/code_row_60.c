#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char* salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char* password, const unsigned char* salt, size_t salt_length, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, salt_length);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hex(const unsigned char* data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter username: ");
    if (fgets(username, USERNAME_LENGTH, stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LENGTH, stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, SALT_LENGTH, hash);

    printf("Username: %s\n", username);
    printf("Salt (hex): ");
    print_hex(salt, SALT_LENGTH);
    printf("Hashed Password (hex with salt): ");
    print_hex(hash, HASH_LENGTH);

    // Here you would typically store the username, salt and hashed password in a database.
    // For demonstration purposes, we are just printing them out.

    return 0;
}