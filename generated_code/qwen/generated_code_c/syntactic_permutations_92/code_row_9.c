#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define SHA256_DIGEST_LENGTH 32

void hash_password(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

void print_hash(unsigned char *digest) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hash);

    printf("Username: %s\n", username);
    printf("Password Hash: ");
    print_hash(hash);

    return 0;
}