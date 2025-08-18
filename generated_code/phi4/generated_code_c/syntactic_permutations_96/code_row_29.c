#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t size) {
    RAND_bytes(salt, size);
}

unsigned char* hash_password(const unsigned char *password, const unsigned char *salt, int password_len, int salt_size, unsigned char **hashed_password_out) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md_type = EVP_sha256();
    
    mdctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(mdctx, md_type, NULL)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    unsigned char hashed_password[EVP_MAX_MD_SIZE];
    int hashed_password_len;

    if (!EVP_DigestUpdate(mdctx, salt, (int)salt_size) ||
        !EVP_DigestUpdate(mdctx, password, password_len) ||
        !EVP_DigestFinal_ex(mdctx, hashed_password, &hashed_password_len)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    *hashed_password_out = malloc(hashed_password_len);
    if (!*hashed_password_out) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    memcpy(*hashed_password_out, hashed_password, hashed_password_len);

    EVP_MD_CTX_free(mdctx);
    return *hashed_password_out;
}

int main() {
    unsigned char salt[SALT_SIZE];
    char username[50], password[100];
    unsigned char *hashed_password;
    int result;

    generate_salt(salt, SALT_SIZE);

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%99s", password);

    result = hash_password((unsigned char *)password, salt, strlen(password), SALT_SIZE, &hashed_password);
    if (result != 1) {
        fprintf(stderr, "Error hashing password\n");
        return EXIT_FAILURE;
    }

    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (size_t i = 0; i < EVP_MD_size(EVP_sha256()); ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    free(hashed_password);

    return EXIT_SUCCESS;
}