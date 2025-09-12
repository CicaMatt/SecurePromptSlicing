#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2)

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % 26;
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[1024];

    snprintf(input, sizeof(input), "%s%s", salt, password);
    SHA256((unsigned char *)input, strlen(input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + i * 2, "%02x", digest[i]);
    }
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing user: %s with hashed password: %s\n", username, salted_hash);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1];
    char salted_hash[HASH_LENGTH + SALT_LENGTH + 2];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    snprintf(salted_hash, sizeof(salted_hash), "%s$%s", salt, hashed_password);

    store_in_database(username, salted_hash);

    return 0;
}