#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void handleErrors(void) {
    fprintf(stderr, "Error occurred.\n");
    exit(EXIT_FAILURE);
}

unsigned char *generate_salt(size_t length) {
    unsigned char *salt = (unsigned char *)malloc(length);
    if (!RAND_bytes(salt, length)) handleErrors();
    return salt;
}

int hash_password(const unsigned char *password, const unsigned char *salt, size_t salt_len, unsigned char *digest) {
    EVP_MD_CTX *mdctx;

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, salt, salt_len)) handleErrors();
    if (1 != EVP_DigestFinal_ex(mdctx, digest, NULL)) handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    unsigned char salt[SALT_LENGTH];
    generate_salt(SALT_LENGTH);

    unsigned char digest[HASH_LENGTH];
    hash_password((unsigned char *)password, salt, SALT_LENGTH, digest);

    // Store the concatenated salt and digest in a database
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    // Normally, you would store the username, salt, and hashed password in a database.

    free(salt);
    return 0;
}