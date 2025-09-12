#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

unsigned char *hash_password(const unsigned char *password, size_t password_len, const unsigned char *salt, size_t salt_len, size_t *output_size) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;
    unsigned char *digest = malloc(EVP_MAX_MD_SIZE);

    if (digest == NULL) handleErrors();

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, salt, salt_len)) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, password, password_len)) handleErrors();

    if (1 != EVP_DigestFinal_ex(mdctx, digest, &md_len)) handleErrors();
    *output_size = md_len;

    EVP_MD_CTX_free(mdctx);
    return digest;
}

void store_hashed_password(const unsigned char *salt, size_t salt_len, const unsigned char *hashed_password, size_t hashed_password_len) {
    // Simulate storing the salt and hashed password in a database
    printf("Storing in 'database':\n");
    printf("Salt: ");
    for (size_t i = 0; i < salt_len; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (size_t i = 0; i < hashed_password_len; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main(void) {
    const unsigned char *salt = (unsigned char *)"fixed_salt";
    size_t salt_len = strlen((const char *)salt);

    char username[256];
    char password[256];

    printf("Enter username: ");
    if (!fgets(username, sizeof(username), stdin)) return 1;
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    if (!fgets(password, sizeof(password), stdin)) return 1;
    password[strcspn(password, "\n")] = 0;

    size_t hashed_password_len;
    unsigned char *hashed_password = hash_password((unsigned char *)password, strlen(password), salt, salt_len, &hashed_password_len);

    store_hashed_password(salt, salt_len, hashed_password, hashed_password_len);
    free(hashed_password);

    return 0;
}