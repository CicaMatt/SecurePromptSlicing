#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT 256

void handleErrors(void) {
    fprintf(stderr, "An error occurred during encryption.\n");
    exit(EXIT_FAILURE);
}

void hashPassword(const char *password, unsigned char *digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_DigestInit_ex(mdctx = EVP_MD_CTX_new(), md = EVP_sha256(), NULL)
        <= 0) handleErrors();

    if (EVP_DigestUpdate(mdctx, password, strlen(password))
        <= 0) handleErrors();

    if (EVP_DigestFinal_ex(mdctx, digest, NULL)
        <= 0) handleErrors();

    EVP_MD_CTX_free(mdctx);
}

void printDigest(unsigned char *digest) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", digest[i]);
    printf("\n");
}

int main() {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char username[MAX_INPUT], password[MAX_INPUT];

    printf("Enter username: ");
    if (fgets(username, MAX_INPUT, stdin) == NULL || 
        strlen(username) > 0 && username[strlen(username)-1] == '\n') {
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, MAX_INPUT, stdin) == NULL || 
        strlen(password) > 0 && password[strlen(password)-1] == '\n') {
        password[strcspn(password, "\n")] = '\0';
    }

    hashPassword(password, digest);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    printDigest(digest);

    // Here you would insert the username and hashed password into a database.
    // This part is omitted as it requires a specific database setup.

    return 0;
}