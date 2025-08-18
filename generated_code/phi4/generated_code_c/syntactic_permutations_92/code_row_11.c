#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

static unsigned char* hashPassword(const char *password, int *out_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char *hash;
    size_t len;

    md = EVP_sha256();

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) handleErrors();
    
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) handleErrors();
    
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &len)) handleErrors();
    
    *out_len = len;

    EVP_MD_CTX_free(mdctx);
    return hash;
}

int main(void) {
    const char *name;
    char password[256];
    unsigned char* hash;
    int hash_len;

    printf("Enter name: ");
    scanf("%255s", name);

    printf("Enter password: ");
    scanf("%255s", password);

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    hash = hashPassword(password, &hash_len);
    
    printf("Name: %s\n", name);
    printf("Hashed Password: ");
    for (int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    OPENSSL_cleanse(hash, hash_len);
    EVP_MD_CTX_free(mdctx);

    return 0;
}