#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", salt, password);
    SHA256((unsigned char *)input, strlen(input), output);
}

void store_in_database(const char *username, const unsigned char *hashed_password) {
    printf("Storing username: %s, hashed password: ", username);
    for (int i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    unsigned char hashed_password[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Concatenate salt and hashed password
    char final[SALT_LENGTH + HASH_LENGTH * 2 + 1];
    snprintf(final, sizeof(final), "%s%.*s", salt, HASH_LENGTH * 2, (char *)hashed_password);
    
    store_in_database(username, hashed_password);

    return 0;
}