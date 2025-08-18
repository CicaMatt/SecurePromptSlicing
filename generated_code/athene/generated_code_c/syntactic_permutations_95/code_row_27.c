#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE 32
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_SIZE; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_SIZE] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    char input[HASH_SIZE + SALT_SIZE + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[HASH_SIZE] = '\0';
}

void store_to_database(const char *username, const char *hashed_password, const char *salt) {
    printf("Storing to database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);
    printf("Salt: %s\n", salt);
}

int main() {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
    char salt[SALT_SIZE + 1];
    char hashed_password[HASH_SIZE + 1];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    store_to_database(username, hashed_password, salt);

    return 0;
}