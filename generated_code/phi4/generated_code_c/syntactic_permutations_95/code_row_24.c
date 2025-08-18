#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

void handleErrors(void) {
    fprintf(stderr, "An error occurred.\n");
    exit(EXIT_FAILURE);
}

int generateSalt(unsigned char *salt, size_t length) {
    if (!RAND_bytes(salt, length)) {
        handleErrors();
    }
    return 1;
}

int hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) handleErrors();

    if (!EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) handleErrors();
    if (!EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) handleErrors();
    if (!EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) handleErrors();
    unsigned int md_len;
    if (!EVP_DigestFinal_ex(mdctx, hash, &md_len)) handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 1;
}

void storeCredentials(const char *username, const unsigned char *saltedHash) {
    // For demonstration purposes, we'll just print the credentials.
    // In a real application, you would store these in a database.
    printf("Storing credentials for username: %s\n", username);
    for (int i = 0; i < SALT_LENGTH + EVP_MAX_MD_SIZE; ++i) {
        printf("%02x", saltedHash[i]);
    }
    printf("\n");
}

void registerUser(const char *username, const char *password) {
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned char saltedHash[SALT_LENGTH + EVP_MAX_MD_SIZE];

    if (!generateSalt(salt, SALT_LENGTH)) handleErrors();
    if (!hashPassword((const unsigned char *)password, salt, hash)) handleErrors();

    memcpy(saltedHash, salt, SALT_LENGTH);
    memcpy(saltedHash + SALT_LENGTH, hash, EVP_MAX_MD_SIZE);

    storeCredentials(username, saltedHash);
}

int main() {
    const char *username = "testuser";
    const char *password = "securepassword";

    registerUser(username, password);

    return 0;
}