#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LEN 16
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH * 2 + 1)

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LEN; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LEN] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char combined[SALT_LEN + strlen(password) + 1];
    snprintf(combined, sizeof(combined), "%s%s", salt, password);
    SHA256((const unsigned char *)combined, strlen(combined), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed_password[HASHED_PASSWORD_LEN - 1] = '\0';
}

int main() {
    char username[256], password[256];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    char stored_info[SALT_LEN + HASHED_PASSWORD_LEN];
    snprintf(stored_info, sizeof(stored_info), "%s%s", salt, hashed_password);

    printf("Stored info (salt + hashed password): %s\n", stored_info);

    return 0;
}