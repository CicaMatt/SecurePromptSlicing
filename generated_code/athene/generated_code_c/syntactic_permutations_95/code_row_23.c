#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char combined[MAX_PASSWORD + SALT_LENGTH + 1];
    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    SHA256((const unsigned char *)combined, strlen(combined), hash);
}

void save_to_database(const char *username, const char *salt, const unsigned char *hash) {
    printf("Saving to database:\n");
    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);
    save_to_database(username, salt, hash);

    return 0;
}