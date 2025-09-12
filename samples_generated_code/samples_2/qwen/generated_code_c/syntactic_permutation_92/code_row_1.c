#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 128
#define HASH_DIGEST_LENGTH EVP_MAX_MD_SIZE

void hash_password(const char *password, unsigned char *digest, unsigned int *digest_len) {
    const EVP_MD *md = EVP_sha256();
    EVP_MD_CTX *mdctx;

    if((mdctx = EVP_MD_CTX_create()) == NULL)
        exit(1);

    if(EVP_DigestInit_ex(mdctx, md, NULL) != 1)
        exit(1);

    if(EVP_DigestUpdate(mdctx, password, strlen(password)) != 1)
        exit(1);

    if(EVP_DigestFinal_ex(mdctx, digest, digest_len) != 1)
        exit(1);

    EVP_MD_CTX_destroy(mdctx);
}

void print_hash(unsigned char *digest, unsigned int digest_len) {
    for (unsigned int i = 0; i < digest_len; ++i)
        printf("%02x", digest[i]);
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    unsigned char digest[HASH_DIGEST_LENGTH];
    unsigned int digest_len;

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD_LEN, stdin) == NULL)
        exit(1);

    password[strcspn(password, "\n")] = 0; // Remove newline character

    hash_password(password, digest, &digest_len);
    printf("Hashed Password: ");
    print_hash(digest, digest_len);

    return 0;
}