#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void hash_password(const unsigned char *password, size_t length, unsigned char **hashed_password, size_t *length_out) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *algorithm = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) exit(EXIT_FAILURE);

    if (1 != EVP_DigestInit_ex(mdctx, algorithm, NULL)) exit(EXIT_FAILURE);

    if (1 != EVP_DigestUpdate(mdctx, password, length)) exit(EXIT_FAILURE);

    *length_out = EVP_MAX_MD_SIZE;
    *hashed_password = malloc(*length_out);
    if (!*hashed_password) {
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_password, length_out)) {
        free(*hashed_password);
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[256];
    unsigned char password[256];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", (char *)password);

    unsigned char *hashed_password;
    size_t hashed_length;

    hash_password(password, strlen((char *)password), &hashed_password, &hashed_length);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for(size_t i = 0; i < hashed_length; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    free(hashed_password);
    return 0;
}