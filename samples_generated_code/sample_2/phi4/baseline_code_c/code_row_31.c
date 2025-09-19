#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include OpenSSL headers
#include <openssl/evp.h>
#include <openssl/rand.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

void hashPassword(const unsigned char *password, size_t password_len, unsigned char **hash_output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    // Select the SHA256 algorithm
    md = EVP_sha256();

    if(!(mdctx = EVP_MD_CTX_new()))
        handleErrors();

    if(1 != EVP_DigestInit_ex(mdctx, md, NULL))
        handleErrors();

    if(1 != EVP_DigestUpdate(mdctx, password, password_len))
        handleErrors();

    unsigned int hash_len;
    *hash_output = (unsigned char *)OPENSSL_malloc(EVP_MD_size(md));
    if(*hash_output == NULL)
        handleErrors();
    
    if(1 != EVP_DigestFinal_ex(mdctx, *hash_output, &hash_len))
        handleErrors();

    // Clean up
    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len-1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len-1] == '\n') {
        password[--len] = '\0';
    }

    unsigned char *hashed_password;
    hashPassword((unsigned char *)password, strlen(password), &hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < EVP_MD_size(EVP_sha256()); ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    OPENSSL_free(hashed_password);

    return 0;
}


To compile and run this code, you need to have OpenSSL installed on your system. You can compile it using a command like:

gcc -o registration_form registration_form.c `pkg-config --cflags --libs openssl`


And then execute the binary with:

./registration_form