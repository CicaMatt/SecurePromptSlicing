#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), hash);
}

int main() {
    char username[100], password[100], salt[SALT_LENGTH + 1];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char hash_str[(HASH_LENGTH * 2) + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    hash_str[(HASH_LENGTH * 2)] = '\0';

    printf("Stored in database:\n");
    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hash_str);

    return 0;
}