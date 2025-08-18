#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define PASSWORD_HASH_LENGTH 20

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int hashPassword(const char *password, unsigned char *digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_DigestInit_ex(&mdctx, EVP_sha1(), NULL) != 1)
        handleErrors();

    md = EVP_get_digestbyname("sha1");
    if (!md)
        handleErrors();

    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1)
        handleErrors();

    unsigned int len;
    if (EVP_DigestFinal_ex(mdctx, digest, &len) != 1)
        handleErrors();
    
    EVP_MD_CTX_free(mdctx);

    return len;
}

int main() {
    const char *username = NULL;
    char password[256] = {0};
    unsigned char hashed_password[PASSWORD_HASH_LENGTH];
    int password_length;

    printf("Enter username: ");
    if (fgets(username, 256, stdin) != NULL) {
        // Remove newline character from the end of username
        size_t len = strlen(username);
        if (len > 0 && username[len-1] == '\n') {
            username[len-1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from the end of password
        size_t len = strlen(password);
        if (len > 0 && password[len-1] == '\n') {
            password[len-1] = '\0';
        }
    }

    password_length = hashPassword(password, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < PASSWORD_HASH_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Here you would insert the username and hashed password into your database
    // For demonstration purposes, this step is omitted

    return 0;
}