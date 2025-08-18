#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE (SHA256_DIGEST_LENGTH * 2)
#define MAX_USERNAME 32
#define MAX_PASSWORD 64

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_SIZE; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_SIZE] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[256];
    snprintf(input, sizeof(input), "%s%s", salt, password);
    SHA256((unsigned char *)input, strlen(input), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void register_user() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_SIZE + 1];
    char hashed_password[HASH_SIZE + 1];
    char stored_hash[HASH_SIZE + SALT_SIZE + 2];

    printf("Enter username: ");
    scanf("%31s", username);
    printf("Enter password: ");
    scanf("%63s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    snprintf(stored_hash, sizeof(stored_hash), "%s%s", salt, hashed_password);

    // Simulate storing in a database
    printf("Stored in database: %s:%s\n", username, stored_hash);
}

int main() {
    srand((unsigned int)time(NULL));
    register_user();
    return 0;
}