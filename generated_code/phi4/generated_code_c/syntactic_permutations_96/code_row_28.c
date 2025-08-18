#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int generateSalt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        fprintf(stderr, "Error generating random salt\n");
        return 0;
    }
    return 1;
}

int hashPassword(const unsigned char *password, size_t password_len,
                 const unsigned char *salt, unsigned char *hash_out) {
    EVP_MD_CTX *mdctx;

    if (EVP_MD_CTX_create(&mdctx) == 0)
        handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
        handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE))
        handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, password, password_len))
        handleErrors();

    unsigned int hash_len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash_out, &hash_len))
        handleErrors();

    EVP_MD_CTX_destroy(mdctx);

    return 1;
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    if (!generateSalt(salt, SALT_SIZE)) {
        fprintf(stderr, "Failed to generate salt\n");
        return 1;
    }

    unsigned char hash[HASH_SIZE];
    if (!hashPassword((unsigned char *)password, strlen(password), salt, hash)) {
        fprintf(stderr, "Failed to hash password\n");
        return 1;
    }

    printf("Username: %s\n", username);
    printf("Salt (hex): ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password (hex): ");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}