#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

void generate_salt(unsigned char *salt, size_t length) {
    if (!RAND_bytes(salt, length)) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();

    if (!(mdctx = EVP_MD_CTX_new())) {
        fprintf(stderr, "Error creating context\n");
        return 0;
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        goto err;
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating digest\n");
        goto err;
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) {
        fprintf(stderr, "Error updating with salt\n");
        goto err;
    }

    size_t outlen;
    *hashed_password = malloc(EVP_MD_size(md));
    if (!*hashed_password) {
        fprintf(stderr, "Memory allocation failed\n");
        goto err;
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_password, &outlen)) {
        fprintf(stderr, "Error finalizing digest\n");
        free(*hashed_password);
        return 0;
    }

    EVP_MD_CTX_free(mdctx);
    return 1;

err:
    EVP_MD_CTX_free(mdctx);
    if (*hashed_password) free(*hashed_password);
    return 0;
}

void store_user(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    // For demonstration purposes, we'll just print the values
    printf("Storing user: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < SALT_LENGTH; ++i)
        printf("%02x", salt[i]);
    printf("\n");

    printf("Hashed Password: ");
    size_t len = strlen((char *)hashed_password); // Assume EVP_MD_size() was used to allocate
    for (size_t i = 0; i < len; ++i)
        printf("%02x", hashed_password[i]);
    printf("\n");
}

int main() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    unsigned char *hashed_password = NULL;
    if (!hash_password((unsigned char *)password, salt, &hashed_password)) {
        fprintf(stderr, "Failed to hash password\n");
        return EXIT_FAILURE;
    }

    store_user(username, salt, hashed_password);
    
    free(hashed_password);
    return 0;
}