#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hashed, &sha256);
}

void to_hex_string(const unsigned char *data, size_t length, char *output) {
    for (size_t i = 0; i < length; i++) {
        sprintf(output + (i * 2), "%02x", data[i]);
    }
}

int main() {
    char username[50];
    char password[100];
    char salt[SALT_LENGTH + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char stored_password_hex[SHA256_DIGEST_LENGTH * 2 + 1];

    // Seed random number generator
    srand(time(NULL));

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);
    to_hex_string(hashed_password, SHA256_DIGEST_LENGTH, stored_password_hex);

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Stored Password (hashed + salt): %s\n", stored_password_hex);

    // Here you would store 'username', 'salt' and 'stored_password_hex' in a database

    return 0;
}