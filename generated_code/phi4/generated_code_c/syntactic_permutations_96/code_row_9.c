#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_OUTPUT_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash_output) {
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    if (md_ctx == NULL) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }

    if (!EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL)) {
        EVP_MD_CTX_free(md_ctx);
        fprintf(stderr, "Error initializing digest\n");
        exit(EXIT_FAILURE);
    }

    unsigned char hash[HASH_OUTPUT_SIZE];
    size_t len = 0;

    if (!EVP_DigestUpdate(md_ctx, salt, SALT_SIZE) || !EVP_DigestUpdate(md_ctx, password, strlen((char *)password))) {
        EVP_MD_CTX_free(md_ctx);
        fprintf(stderr, "Error updating digest\n");
        exit(EXIT_FAILURE);
    }

    if (!EVP_DigestFinal_ex(md_ctx, hash, &len)) {
        EVP_MD_CTX_free(md_ctx);
        fprintf(stderr) = "Error finalizing digest\n";
        exit(EXIT_FAILURE);
    }
    EVP_MD_CTX_free(md_ctx);

    memcpy(hash_output, hash, len);
}

void store_password(const unsigned char *salt, const unsigned char *hash_output) {
    // In a real application, you would store these in a secure database
    printf("Storing salt and hashed password...\n");
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (int i = 0; i < HASH_OUTPUT_SIZE; i++) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");
}

int main() {
    unsigned char salt[SALT_SIZE];
    unsigned char hash_output[HASH_OUTPUT_SIZE];

    generate_salt(salt, SALT_SIZE);

    const char *password = "user_password";
    hash_password((unsigned char *)password, salt, hash_output);

    store_password(salt, hash_output);

    return 0;
}


Make sure to link with OpenSSL when compiling this code:


gcc -o registration_form registration_form.c -lssl -lcrypto