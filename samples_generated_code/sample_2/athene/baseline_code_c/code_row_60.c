#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2)
#define BUFFER_SIZE (HASH_LENGTH + SALT_LENGTH + 1)

void generate_salt(char *salt, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char combined[BUFFER_SIZE];
    snprintf(combined, sizeof(combined), "%s%s", salt, password);
    SHA256((unsigned char *)combined, strlen(combined), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void register_user(const char *username, const char *password) {
    char salt[SALT_LENGTH + 1];
    generate_salt(salt, SALT_LENGTH);

    char hashed_password[BUFFER_SIZE];
    hash_password(password, salt, hashed_password);

    char combined[BUFFER_SIZE];
    snprintf(combined, sizeof(combined), "%s%s", salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Stored in database: %s\n", combined);
}

int main() {
    const char *username = "example_user";
    const char *password = "example_password";

    register_user(username, password);

    return 0;
}