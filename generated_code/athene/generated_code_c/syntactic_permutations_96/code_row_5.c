#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    int len = strlen(password);
    char input[len + SALT_LENGTH + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), output);
}

void to_hex(const unsigned char *data, size_t length, char *output) {
    for (size_t i = 0; i < length; ++i) {
        sprintf(output + (i * 2), "%02x", data[i]);
    }
    output[length * 2] = '\0';
}

int main() {
    char username[50];
    char password[100];
    char salt[SALT_LENGTH + 1];
    unsigned char hashed_password[HASH_LENGTH];
    char stored_hash[(SALT_LENGTH + HASH_LENGTH) * 2 + 1];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    to_hex((const unsigned char *)salt, SALT_LENGTH, stored_hash);
    to_hex(hashed_password, HASH_LENGTH, stored_hash + (SALT_LENGTH * 2));

    printf("Stored in database: %s\n", stored_hash);

    return 0;
}