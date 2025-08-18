#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random bytes for salt.\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, size_t password_len,
                   const unsigned char *salt, size_t salt_size,
                   unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    mdctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing hash context.\n");
        exit(EXIT_FAILURE);
    }
    
    if (!EVP_DigestUpdate(mdctx, password, password_len)) {
        fprintf(stderr, "Error updating hash context with password.\n");
        exit(EXIT_FAILURE);
    }

    if (!EVP_DigestUpdate(mdctx, salt, salt_size)) {
        fprintf(stderr, "Error updating hash context with salt.\n");
        exit(EXIT_FAILURE);
    }
    
    if (!EVP_DigestFinal_ex(mdctx, hash, NULL)) {
        fprintf(stderr, "Error finalizing hash.\n");
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
    hash_password((unsigned char *)password, strlen(password), salt, SALT_SIZE, hash);

    // Append the salt to the hashed password
    unsigned char *hashed_with_salt = malloc(HASH_SIZE + SALT_SIZE);
    memcpy(hashed_with_salt, hash, HASH_SIZE);
    memcpy(hashed_with_salt + HASH_SIZE, salt, SALT_SIZE);

    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (int i = 0; i < HASH_SIZE + SALT_SIZE; ++i) {
        printf("%02x", hashed_with_salt[i]);
    }
    printf("\n");

    free(hashed_with_salt);

    // Note: Store the username, and hashed_with_salt in your database here
    return 0;
}