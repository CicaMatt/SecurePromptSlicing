#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

unsigned char *hashPassword(const unsigned char *password, size_t length, int *olen) {
    EVP_MD_CTX *ctx;
    const EVP_MD *md;

    if(!(md = EVP_get_digestbyname("SHA256"))) {
        handleErrors();
    }

    if(!(ctx = EVP_MD_CTX_new())) {
        handleErrors();
    }
    
    if(1 != EVP_DigestInit_ex(ctx, md, NULL)) {
        handleErrors();
    }
    
    if(1 != EVP_DigestUpdate(ctx, password, length)) {
        handleErrors();
    }

    unsigned char *md_value = malloc(EVP_MD_size(md));
    if(!md_value) {
        handleErrors();
    }

    if(1 != EVP_DigestFinal_ex(ctx, md_value, olen)) {
        handleErrors();
    }

    EVP_MD_CTX_free(ctx);
    
    return md_value;
}

int main(void) {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    int len;
    unsigned char *hashed_password = hashPassword((unsigned char *)password, strlen(password), &len);

    printf("Username: %s\n", username);
    printf("Hashed Password (SHA256): ");
    for(int i = 0; i < len; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    free(hashed_password);

    return 0;
}