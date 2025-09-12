#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < SALT_LENGTH; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hashed_password) {
    char combined[256];
    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    SHA256((const unsigned char *)combined, strlen(combined), hashed_password);
}

void store_user(const char *username, const char *salted_hash) {
    printf("Storing user: %s with hash: %s\n", username, salted_hash);
    // Normally you would interact with a real database here
}

int main() {
    srand(time(NULL));

    char username[100], password[100];
    char salt[SALT_LENGTH + 1];
    unsigned char hashed_password[HASH_LENGTH * 2 + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Convert binary hash to hex string
    char hex_hash[HASH_LENGTH * 2 + 1];
    for (int i = 0; i < HASH_LENGTH; ++i) {
        sprintf(hex_hash + (i * 2), "%02x", hashed_password[i]);
    }

    // Combine salt and hex hash
    snprintf((char *)hashed_password, sizeof(hashed_password), "%s%s", hex_hash, salt);

    store_user(username, (const char *)hashed_password);

    return 0;
}