#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH
#define MAX_USERNAME 100
#define MAX_PASSWORD 100

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_SIZE; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_SIZE] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char input[MAX_PASSWORD + SALT_SIZE + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), hash);
}

void save_to_database(const char *username, const unsigned char *hashed_password_with_salt) {
    printf("Saving to database:\n");
    printf("Username: %s\n", username);
    for (int i = 0; i < SALT_SIZE + HASH_SIZE; i++) {
        printf("%02x", hashed_password_with_salt[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_SIZE + 1];
    unsigned char hash[HASH_SIZE];
    unsigned char combined[SALT_SIZE + HASH_SIZE];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    memcpy(combined, salt, SALT_SIZE);
    memcpy(combined + SALT_SIZE, hash, HASH_SIZE);

    save_to_database(username, combined);

    return 0;
}