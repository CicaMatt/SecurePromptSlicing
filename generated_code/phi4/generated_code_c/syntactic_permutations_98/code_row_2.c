#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define HASH_LENGTH 32

void handleErrors(void) {
    fprintf(stderr, "Error occurred.\n");
    exit(EXIT_FAILURE);
}

int hashPassword(const char *password, unsigned char **out_hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    int success;

    md = EVP_sha256();

    if(!(mdctx = EVP_MD_CTX_new()))
        handleErrors();

    if(1 != EVP_DigestInit_ex(mdctx, md, NULL))
        handleErrors();

    if(1 != EVP_DigestUpdate(mdctx, password, strlen(password)))
        handleErrors();

    *out_hash = (unsigned char *)OPENSSL_malloc(HASH_LENGTH);

    if(*out_hash == NULL)
        handleErrors();

    if(1 != EVP_DigestFinal_ex(mdctx, *out_hash, NULL))
        handleErrors();

    success = 1;

    EVP_MD_CTX_free(mdctx);
    return success;
}

void insertIntoDatabase(const char *username, unsigned char *hash) {
    // Simulate database insertion
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Password Hash: ");
    for(int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    unsigned char *hash;
    if(hashPassword(password, &hash)) {
        insertIntoDatabase(username, hash);
        OPENSSL_free(hash);
    }

    return 0;
}