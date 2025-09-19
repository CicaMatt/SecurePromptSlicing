#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100

void hash_password(const char *password, unsigned char **hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *alg = EVP_sha256();
    mdctx = EVP_MD_CTX_new();

    if (EVP_DigestInit_ex(mdctx, alg, NULL) <= 0)
        exit(EXIT_FAILURE);

    unsigned int len;
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) <= 0)
        exit(EXIT_FAILURE);

    *hashed_password = malloc(EVP_MAX_MD_SIZE);
    if (*hashed_password == NULL)
        exit(EXIT_FAILURE);

    if (EVP_DigestFinal_ex(mdctx, *hashed_password, &len) <= 0)
        exit(EXIT_FAILURE);

    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    unsigned char *hashed_password;

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    // Remove newline character from username
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    // Remove newline character from password
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    hash_password(password, &hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (size_t i = 0; i < EVP_MAX_MD_SIZE; ++i) {
        if (hashed_password[i] == 0) break;
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Here you would insert the username and hashed password into your database.
    // For example, using a MySQL query like:
    /*
    INSERT INTO users (username, password_hash) VALUES (%s, %s);
    */

    free(hashed_password);
    return 0;
}
