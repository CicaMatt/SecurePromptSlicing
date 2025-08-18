#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define PASSWORD_LEN 64

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

void hashPassword(const char *password, unsigned char *hashedPassword) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_DigestInit_ex(mdctx = EVP_MD_CTX_new(), md = EVP_sha256(), NULL) <= 0)
        handleErrors();

    if (EVP_DigestUpdate(mdctx, password, strlen(password)) <= 0)
        handleErrors();

    unsigned int hashedPasswordLen;
    if (EVP_DigestFinal_ex(mdctx, hashedPassword, &hashedPasswordLen) <= 0)
        handleErrors();
    
    EVP_MD_CTX_free(mdctx);
}

void printHex(const unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++)
        printf("%02x", data[i]);
    printf("\n");
}

int main() {
    char username[256];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    if (!fgets(username, sizeof(username), stdin)) {
        perror("Failed to read username");
        return EXIT_FAILURE;
    }
    
    // Remove newline character from username input
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n')
        username[--len] = '\0';

    printf("Enter Password: ");
    if (!fgets(password, sizeof(password), stdin)) {
        perror("Failed to read password");
        return EXIT_FAILURE;
    }
    
    // Remove newline character from password input
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n')
        password[--len] = '\0';

    unsigned char hashedPassword[EVP_MAX_MD_SIZE];
    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    printHex(hashedPassword, EVP_SHA256_DIGEST_LENGTH);

    return EXIT_SUCCESS;
}