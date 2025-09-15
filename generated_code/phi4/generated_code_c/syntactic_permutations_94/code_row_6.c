#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT_SIZE 16

// Function to generate a random salt
void generate_salt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, size, fp);
    fclose(fp);
}

// Function to hash a password using SHA-256 with salt
void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *alg = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        perror("Error creating EVP_MD_CTX");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, alg, NULL)) {
        perror("Error initializing digest");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        perror("Error updating digest with salt");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        perror("Error updating digest with password");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    unsigned int len;
    if (1 != EVP_DigestFinal_ex(mdctx, output, &len)) {
        perror("Error finalizing digest");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }
    EVP_MD_CTX_free(mdctx);

    // Null-terminate the hash
    output[len] = '\0';
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password[EVP_MAX_MD_SIZE];
    hash_password((unsigned char *)password, salt, hashed_password);

    // Convert salt and hash to hex string for storage
    char salt_hex[2 * SALT_SIZE + 1];
    char hash_hex[2 * EVP_MAX_MD_SIZE + 1];

    for (int i = 0; i < SALT_SIZE; ++i) {
        sprintf(&salt_hex[i * 2], "%02x", salt[i]);
    }
    salt_hex[SALT_SIZE * 2] = '\0';

    for (unsigned int i = 0; i < strlen((const char *)hashed_password); ++i) {
        sprintf(&hash_hex[i * 2], "%02x", hashed_password[i]);
    }
    hash_hex[strlen((const char *)hashed_password) * 2] = '\0';

    // Normally, you would insert the username, salt_hex, and hash_hex into a database here.
    printf("Username: %s\n", username);
    printf("Salt (hex): %s\n", salt_hex);
    printf("Hashed Password (hex): %s\n", hash_hex);

    return 0;
}
