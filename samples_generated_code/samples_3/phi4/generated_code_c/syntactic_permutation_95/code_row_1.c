#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void handleErrors(void) {
    fprintf(stderr, "Error occurred\n");
    exit(EXIT_FAILURE);
}

unsigned char *generateSalt(size_t size, unsigned char *buffer) {
    if (!RAND_bytes(buffer, size)) {
        handleErrors();
    }
    return buffer;
}

int hashPassword(const char *password, const unsigned char *salt, unsigned char **hashedPassword) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) handleErrors();

    unsigned int len;
    *hashedPassword = malloc(HASH_SIZE);
    if (!*hashedPassword) handleErrors();

    if (1 != EVP_DigestFinal_ex(mdctx, *hashedPassword, &len)) handleErrors();
    EVP_MD_CTX_free(mdctx);

    return len;
}

void storeCredentials(const char *username, const unsigned char *salt, const unsigned char *hashedPassword) {
    printf("Storing credentials for user: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");
    
    printf("Hashed Password: ");
    for (unsigned int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    // Here you would store the username, salt, and hashed password in a database.
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char salt[SALT_SIZE];
    generateSalt(SALT_SIZE, salt);

    unsigned char *hashedPassword;
    hashPassword(password, salt, &hashedPassword);

    storeCredentials(username, salt, hashedPassword);

    free(hashedPassword);
    return 0;
}