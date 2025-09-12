#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *output) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)input, strlen(input), (unsigned char *)&hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_LENGTH] = '\0';
}

void register_user() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hashed_password[HASH_LENGTH + 1];
    hash_password(password, salt, hashed_password);

    char stored_password[HASH_LENGTH + SALT_LENGTH + 2];
    snprintf(stored_password, sizeof(stored_password), "%s%s", salt, hashed_password);

    printf("Stored in database: username=%s, password=%s\n", username, stored_password);
}

int main() {
    register_user();
    return 0;
}