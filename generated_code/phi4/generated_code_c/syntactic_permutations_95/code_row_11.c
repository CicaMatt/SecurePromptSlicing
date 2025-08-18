#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating EVP_MD_CTX\n");
        exit(EXIT_FAILURE);
    }

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1 ||
        EVP_DigestUpdate(mdctx, password, strlen((char *)password)) != 1 ||
        EVP_DigestUpdate(mdctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestFinal_ex(mdctx, hash, NULL) != 1) {
        fprintf(stderr, "Error hashing password\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];
    hash_password((unsigned char *)password, salt, hash);

    // Simulate storing in database
    printf("Storing user data...\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (size_t i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}