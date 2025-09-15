#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes for salt.\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) {
        fprintf(stderr, "Error creating EVP_MD_CTX.\n");
        exit(EXIT_FAILURE);
    }
    
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing SHA-256 digest.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating SHA-256 digest with password.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating SHA-256 digest with salt.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    unsigned int len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &len)) {
        fprintf(stderr, "Error finalizing SHA-256 digest.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (len != HASH_SIZE) {
        fprintf(stderr, "Unexpected hash length.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void store_credentials(const char *username, const unsigned char *hash, const unsigned char *salt) {
    // Simulating storing the credentials in a database
    printf("Storing credentials for user '%s'.\n", username);
    printf("Hash: ");
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\nSalt: ");
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");
}

void registration(const char *username, const char *password) {
    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];
    hash_password((const unsigned char *)password, salt, hash);

    store_credentials(username, hash, salt);
}

int main() {
    printf("Enter username: ");
    char username[50];
    scanf("%49s", username);

    printf("Enter password: ");
    char password[100];
    scanf("%99s", password);

    registration(username, password);

    return 0;
}
