#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + (rand() % ('Z' - 'A' + 1));
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), output);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    unsigned char hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Concatenate salt and hashed password
    memcpy(hashed_password + HASH_LENGTH, salt, SALT_LENGTH);
    hashed_password[HASH_LENGTH + SALT_LENGTH] = '\0';

    printf("Stored in database: %s:%s\n", username, hashed_password);

    return 0;
}