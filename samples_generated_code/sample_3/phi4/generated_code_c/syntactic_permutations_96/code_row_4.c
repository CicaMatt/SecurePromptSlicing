#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

void generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Failed to generate salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hash_output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();
    if (md == NULL) {
        fprintf(stderr, "SHA-256 is not available\n");
        exit(EXIT_FAILURE);
    }

    mdctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Digest initialization failed\n");
        exit(EXIT_FAILURE);
    }
    
    EVP_DigestUpdate(mdctx, salt, SALT_LENGTH);
    EVP_DigestUpdate(mdctx, password, strlen((const char *)password));
    
    size_t len;
    *hash_output = malloc(EVP_MD_size(md));
    if (!EVP_DigestFinal_ex(mdctx, *hash_output, &len)) {
        fprintf(stderr, "Digest finalization failed\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void store_credentials(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    // Simulating storage in a database by printing to stdout
    printf("Storing credentials for user '%s'\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    size_t hash_len = EVP_MD_size(EVP_sha256());
    for (size_t i = 0; i < hash_len; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[50];
    char password[100];

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    unsigned char *hashed_password;
    hash_password((unsigned char *)password, salt, &hashed_password);

    store_credentials(username, salt, hashed_password);

    free(hashed_password);
    return 0;
}