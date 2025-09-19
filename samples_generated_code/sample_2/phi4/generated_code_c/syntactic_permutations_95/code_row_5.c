#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        fprintf(stderr, "Error generating random bytes for salt.\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (!(md = EVP_get_digestbyname("sha256"))) {
        fprintf(stderr, "Unknown message digest\n");
        exit(EXIT_FAILURE);
    }

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating hash context.\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing hash.\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        fprintf(stderr, "Error updating hash with password.\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating hash with salt.\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, NULL)) {
        fprintf(stderr, "Error finalizing hash.\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // This function should handle storing the username and salted hash to a database.
    // For demonstration purposes, we'll just print it.
    printf("Storing credentials for user: %s\n", username);
    printf("Salted Hash: ");
    for (int i = 0; i < SALT_SIZE + HASH_SIZE; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

void register_user() {
    char username[100];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];
    unsigned char salted_hash[SALT_SIZE + HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    fflush(stdout); // Ensure 'Enter' key is processed immediately
    fgets(hash, sizeof(hash), stdin);
    hash[strcspn((char *)hash, "\n")] = 0; // Remove newline character

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char *)hash, salt, hash);

    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, hash, HASH_SIZE);

    store_credentials(username, salted_hash);
}

int main() {
    register_user();
    return 0;
}
