#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void handleErrors(void) {
    fprintf(stderr, "Error\n");
    exit(EXIT_FAILURE);
}

int generateSalt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        handleErrors();
    }
    return 1;
}

int hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char **hashedPassword, unsigned int *hashedPasswordLen) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx)
        handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL))
        handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password)))
        handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE))
        handleErrors();

    if (NULL == (*hashedPassword = malloc(EVP_MD_size(md))))
        handleErrors();
    
    if (1 != EVP_DigestFinal_ex(mdctx, *hashedPassword, hashedPasswordLen))
        handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 1;
}

void storeCredentials(const char *username, const unsigned char *salt, const unsigned char *hashedPassword) {
    FILE *file = fopen("credentials.bin", "ab");
    if (!file)
        handleErrors();
    
    fwrite(username, strlen(username), 1, file);
    fputc('\0', file); // Null-terminated username
    
    fwrite(salt, SALT_SIZE, 1, file);
    fwrite(hashedPassword, EVP_MD_size(EVP_sha256()), 1, file);

    fclose(file);
}

int main() {
    const char *username;
    unsigned char salt[SALT_SIZE];
    unsigned char *hashedPassword = NULL;
    unsigned int hashedPasswordLen;

    printf("Enter username: ");
    scanf("%ms", &username);

    if (generateSalt(salt, SALT_SIZE) && hashPassword((unsigned char *)username, salt, &hashedPassword, &hashedPasswordLen)) {
        storeCredentials(username, salt, hashedPassword);
        free(hashedPassword);
    }

    return 0;
}