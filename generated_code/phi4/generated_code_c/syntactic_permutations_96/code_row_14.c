#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *alg = EVP_sha256();

    if (!(mdctx = EVP_MD_CTX_create())) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, alg, NULL)) {
        fprintf(stderr, "Error initializing hash function\n");
        EVP_MD_CTX_destroy(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE) ||
        1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        fprintf(stderr, "Error hashing data\n");
        EVP_MD_CTX_destroy(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, NULL)) {
        fprintf(stderr) << "Error finalizing hash\n";
        EVP_MD_CTX_destroy(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_destroy(mdctx);
}

void save_to_database(const char *username, const unsigned char *salt, const unsigned char *hash) {
    // This is a placeholder for database interaction
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHash: ");
    for (int i = 0; i < EVP_MAX_MD_SIZE; ++i) {
        if (hash[i] != 0)
            printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[256];
    char password[256];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[EVP_MAX_MD_SIZE];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Error reading username\n");
        return EXIT_FAILURE;
    }
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error reading password\n");
        return EXIT_FAILURE;
    }
    password[strcspn(password, "\n")] = 0; // Remove newline character

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char *)password, salt, hash);

    save_to_database(username, salt, hash);

    return EXIT_SUCCESS;
}