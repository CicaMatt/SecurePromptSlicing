#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

// Function to hash the password using SHA256
void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    EVP_MD_CTX *mdctx;

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        fprintf(stderr, "Error updating digest\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, outputBuffer, NULL)) {
        fprintf(stderr, "Error finalizing digest\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

// Function to convert binary hash to hexadecimal string
void bin_to_hex(const unsigned char *binary, size_t len, char *hexString) {
    static const char hex_chars[] = "0123456789abcdef";
    for (size_t i = 0; i < len; i++) {
        sprintf(hexString + (i * 2), "%c%c", hex_chars[(unsigned char)(binary[i] >> 4)],
                hex_chars[(unsigned char)(binary[i] & 0x0F)]);
    }
}

int main() {
    const unsigned int MAX_USERNAME = 256;
    const unsigned int MAX_PASSWORD = 256;

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char hexHash[2 * SHA256_DIGEST_LENGTH + 1];

    printf("Enter Username: ");
    if (fgets(username, MAX_USERNAME, stdin) == NULL) {
        fprintf(stderr, "Error reading username\n");
        exit(EXIT_FAILURE);
    }
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    if (fgets(password, MAX_PASSWORD, stdin) == NULL) {
        fprintf(stderr, "Error reading password\n");
        exit(EXIT_FAILURE);
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    hash_password(password, hash);
    bin_to_hex(hash, SHA256_DIGEST_LENGTH, hexHash);

    printf("Username: %s\n", username);
    printf("Password Hash (SHA-256): %s\n", hexHash);

    // Here you would insert the username and hashed password into your database.
    // This example does not include actual database operations.

    return 0;
}


**Note:** Before running this code, ensure that OpenSSL is installed on your system. You might need to link against OpenSSL libraries by adding `-lssl -lcrypto` to your compiler command, e.g., `gcc program.c -o program -lssl -lcrypto`.