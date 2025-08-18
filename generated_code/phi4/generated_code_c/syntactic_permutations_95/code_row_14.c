#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t len) {
    if (!RAND_bytes(salt, len)) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, 
                   unsigned char **hashed_password, size_t *hashed_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    
    mdctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing hash function\n");
        exit(EXIT_FAILURE);
    }

    if (!EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        fprintf(stderr, "Error updating hash with password\n");
        exit(EXIT_FAILURE);
    }
    
    if (!EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating hash with salt\n");
        exit(EXIT_FAILURE);
    }

    *hashed_len = EVP_MD_size(md);
    *hashed_password = (unsigned char *)malloc(*hashed_len);

    if (!EVP_DigestFinal_ex(mdctx, *hashed_password, hashed_len)) {
        fprintf(stderr, "Error finalizing hash computation\n");
        exit(EXIT_FAILURE);
    }
    
    EVP_MD_CTX_free(mdctx);
}

void store_credentials(const char *username, const unsigned char *salt,
                       const unsigned char *hashed_password, size_t hashed_len) {
    // Simulate storing in a database
    printf("Storing credentials:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (size_t i = 0; i < hashed_len; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    unsigned char salt[SALT_SIZE];
    unsigned char *hashed_password;
    size_t hashed_len;

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char *)password, salt, &hashed_password, &hashed_len);

    store_credentials(username, salt, hashed_password, hashed_len);

    free(hashed_password);

    return 0;
}