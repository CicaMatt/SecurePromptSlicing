#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT_SIZE 256

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

char* hashPassword(const char *password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;

    if (!(md = EVP_get_digestbyname("sha256")))
        handleErrors();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx)
        handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL))
        handleErrors();

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password)))
        handleErrors();

    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len))
        handleErrors();
    
    EVP_MD_CTX_free(mdctx);

    char *hashedPassword = (char *)malloc((md_len + 1) * sizeof(char));
    for (i = 0; i < md_len; i++)
        sprintf(&hashedPassword[i*2], "%02x", (unsigned int)md_value[i]);
    hashedPassword[md_len*2] = '\0';
    
    return hashedPassword;
}

void insertIntoDatabase(const char *username, const char *hashedPassword) {
    // Placeholder for database insertion logic
    printf("Inserting into database: Username=%s, Hashed Password=%s\n", username, hashedPassword);
}

int main() {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];

    printf("Enter username: ");
    if (fgets(username, MAX_INPUT_SIZE, stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, MAX_INPUT_SIZE, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    char *hashedPassword = hashPassword(password);

    insertIntoDatabase(username, hashedPassword);

    free(hashedPassword);

    return 0;
}
