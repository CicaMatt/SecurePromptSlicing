#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASHED_PASSWORD_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    RAND_bytes(salt, salt_size);
}

unsigned int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *out_hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();

    if (!(mdctx = EVP_MD_CTX_new())) return 0;

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    unsigned int md_len;

    if (1 != EVP_DigestFinal_ex(mdctx, out_hash, &md_len)) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }
    
    EVP_MD_CTX_free(mdctx);

    return md_len;
}

void store_credentials(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    // Simulated database storage
    printf("Storing credentials for user: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASHED_PASSWORD_SIZE; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    unsigned char salt[SALT_SIZE];
    unsigned char hashed_password[HASHED_PASSWORD_SIZE];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_SIZE);

    if (hash_password((unsigned char *)password, salt, hashed_password) == 0) {
        fprintf(stderr, "Failed to hash password\n");
        return EXIT_FAILURE;
    }

    store_credentials(username, salt, hashed_password);

    return EXIT_SUCCESS;
}