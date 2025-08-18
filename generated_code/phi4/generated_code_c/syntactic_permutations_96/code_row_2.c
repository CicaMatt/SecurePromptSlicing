#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(EXIT_FAILURE);
    }
}

unsigned char *hash_password(const unsigned char *password, const unsigned char *salt, int *result_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char *ciphertext;

    if (!(md = EVP_sha256())) {
        fprintf(stderr, "Error: SHA-256 not available\n");
        exit(EXIT_FAILURE);
    }

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating digest context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating digest with password\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt\n");
        exit(EXIT_FAILURE);
    }

    ciphertext = malloc(EVP_MAX_MD_SIZE);

    if (!ciphertext) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, ciphertext, result_len)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);

    return ciphertext;
}

void store_credentials(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    printf("Storing credentials for user: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    int hash_len;
    const unsigned char *hash_ptr = hashed_password;
    while (*hash_ptr) {
        printf("%02x", *(unsigned char *)hash_ptr);
        ++hash_ptr;
    }
    printf("\n");
}

int main() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        username[strcspn(username, "\n")] = 0; // Remove newline character
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin)) {
        password[strcspn(password, "\n")] = 0; // Remove newline character
    }

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    int hash_len;
    unsigned char *hashed_password = hash_password((unsigned char *)password, salt, &hash_len);

    store_credentials(username, salt, hashed_password);

    free(hashed_password);

    return 0;
}