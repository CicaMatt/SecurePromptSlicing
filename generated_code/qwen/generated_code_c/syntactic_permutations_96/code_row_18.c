#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define HASH_DIGEST_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_in_database(const char *username, const unsigned char *hash) {
    // Simulating database storage by printing to console
    printf("Storing username: %s\n", username);
    printf("Hashed password: ");
    for (int i = 0; i < HASH_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    unsigned char hash[HASH_DIGEST_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hash);

    store_in_database(username, hash);

    return 0;
}