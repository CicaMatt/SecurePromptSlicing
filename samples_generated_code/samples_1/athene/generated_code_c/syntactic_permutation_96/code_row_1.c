#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[HASH_LENGTH + SALT_LENGTH + 1];
    snprintf(input, sizeof(input), "%s%s", salt, password);
    SHA256((unsigned char *)input, strlen(input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password_with_salt) {
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password_with_salt);
}

int main() {
    char username[100], password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1];
    char stored_value[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    snprintf(stored_value, sizeof(stored_value), "%s%s", salt, hashed_password);
    store_in_database(username, stored_value);

    return 0;
}