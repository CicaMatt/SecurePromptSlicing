#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 8
#define PASSWORD_MAX_LENGTH 128

void generate_salt(char *salt, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *digest) {
    size_t password_length = strlen(password);
    size_t salt_length = strlen(salt);
    unsigned char *input = malloc(password_length + salt_length);

    memcpy(input, password, password_length);
    memcpy(input + password_length, salt, salt_length);

    SHA256(input, password_length + salt_length, digest);
    free(input);
}

void print_digest(unsigned char *digest) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[PASSWORD_MAX_LENGTH + 1];
    char salt[SALT_LENGTH + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%128s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    printf("Salt: %s\n", salt);
    printf("Hashed Password: ");
    print_digest(hashed_password);

    return 0;
}