#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors(void) {
    fputs("An error occurred\n", stderr);
    exit(EXIT_FAILURE);
}

int hashPassword(const unsigned char *password, size_t password_len, unsigned char **hashed_password, size_t *hashed_length) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    
    if(!(mdctx = EVP_MD_CTX_new())) handleErrors();

    if(1 != EVP_DigestInit_ex(mdctx, md, NULL)) handleErrors();
    if(1 != EVP_DigestUpdate(mdctx, password, password_len)) handleErrors();
    if(1 != EVP_DigestFinal_ex(mdctx, NULL, hashed_length)) handleErrors();

    *hashed_password = (unsigned char *)malloc(*hashed_length);
    if(!*hashed_password) handleErrors();

    if(1 != EVP_DigestInit_ex(mdctx, md, NULL)) handleErrors();
    if(1 != EVP_DigestUpdate(mdctx, password, password_len)) handleErrors();
    if(1 != EVP_DigestFinal_ex(mdctx, *hashed_password, hashed_length)) handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 0;
}

int main() {
    char username[100];
    char password[100];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned char *hashed_password;
    size_t hashed_length;

    hashPassword((unsigned char *)password, strlen(password), &hashed_password, &hashed_length);

    char salted_hash[256];
    snprintf(salted_hash, sizeof(salted_hash), "%s:%.*s", username, (int)hashed_length, hashed_password);
    
    printf("Storing in database: %s\n", salted_hash);

    free(hashed_password);

    return 0;
}