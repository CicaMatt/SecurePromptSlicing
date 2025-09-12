#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT_SIZE 256

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

unsigned char* hashPassword(const unsigned char *password, size_t password_len, unsigned int *digest_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char *ciphertext;

    md = EVP_sha256();

    if(!(mdctx = EVP_MD_CTX_new())) handleErrors();
    
    if(1 != EVP_DigestInit_ex(mdctx, md, NULL)) handleErrors();
    
    if(1 != EVP_DigestUpdate(mdctx, password, password_len)) handleErrors();
    
    ciphertext = malloc(EVP_MAX_MD_SIZE);
    if(!ciphertext) handleErrors();

    if(1 != EVP_DigestFinal_ex(mdctx, ciphertext, digest_len)) handleErrors();
    
    EVP_MD_CTX_free(mdctx);

    return ciphertext;
}

int main(void) {
    char username[MAX_INPUT_SIZE];
    unsigned char password[MAX_INPUT_SIZE];

    printf("Enter username: ");
    fgets(username, MAX_INPUT_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets((char *)password, MAX_INPUT_SIZE, stdin);
    size_t password_len = strlen((char *)password) - 1; // exclude newline
    password[password_len] = '\0'; // remove newline

    unsigned int digest_len;
    unsigned char *hashed_password = hashPassword(password, (unsigned int)password_len, &digest_len);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for(unsigned int i = 0; i < digest_len; i++)
        printf("%02x", hashed_password[i]);
    printf("\n");

    free(hashed_password);

    return 0;
}