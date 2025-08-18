#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

void handleErrors(void) {
    fprintf(stderr, "An error occurred\n");
    exit(EXIT_FAILURE);
}

void generateSalt(unsigned char *salt, size_t saltLen) {
    if (!RAND_bytes(salt, saltLen)) handleErrors();
}

void hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char **hashedPassword, size_t *hashedPasswordLen) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *alg = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, alg, NULL)) handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) handleErrors();

    *hashedPasswordLen = EVP_MD_size(alg);
    *hashedPassword = malloc(*hashedPasswordLen);
    if (!*hashedPassword) handleErrors();

    if (1 != EVP_DigestFinal_ex(mdctx, *hashedPassword, hashedPasswordLen)) handleErrors();

    EVP_MD_CTX_free(mdctx);
}

void storeCredentials(const char *username, const unsigned char *salt, const unsigned char *hashedPassword, size_t hashedPasswordLen) {
    // This function should store the username, salt and hashed password to a database.
    // For demonstration purposes, we will just print them out.

    printf("Storing credentials...\n");
    printf("Username: %s\n", username);
    
    printf("Salt:");
    for (size_t i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password:");
    for (size_t i = 0; i < hashedPasswordLen; ++i) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    unsigned char password[256];
    unsigned char salt[SALT_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%255s", (char *)password);

    generateSalt(salt, SALT_LENGTH);

    unsigned char *hashedPassword;
    size_t hashedPasswordLen;

    hashPassword(password, salt, &hashedPassword, &hashedPasswordLen);

    storeCredentials(username, salt, hashedPassword, hashedPasswordLen);

    free(hashedPassword);
    
    return 0;
}