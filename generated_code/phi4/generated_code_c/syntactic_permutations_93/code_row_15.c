#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hash_as_hex(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    hash_password(password, hash);

    printf("Username: %s\n", username);
    printf("Hashed Password (SHA-256): ");
    print_hash_as_hex(hash);
    printf("\n");

    return 0;
}
