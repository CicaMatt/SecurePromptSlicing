#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

void handleErrors(void) {
    fprintf(stderr, "An error occurred\n");
    exit(EXIT_FAILURE);
}

int generateSalt(unsigned char *salt) {
    if (!RAND_bytes(salt, SALT_LENGTH)) {
        handleErrors();
    }
    return 1;
}

int hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) handleErrors();

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, password, strlen((char *)password)) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, salt, SALT_LENGTH) != 1) handleErrors();
    if (EVP_DigestFinal_ex(mdctx, hash, NULL) != 1) handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 1;
}

int main() {
    unsigned char password[256], salt[SALT_LENGTH], hash[EVP_MAX_MD_SIZE];
    int hash_len;

    printf("Enter username: ");
    char username[100];
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets((char *)password, sizeof(password), stdin);
    password[strcspn((char *)password, "\n")] = 0; // Remove newline

    if (!generateSalt(salt)) handleErrors();

    if (!hashPassword(password, salt, hash)) handleErrors();
    
    hash_len = EVP_MD_size(EVP_sha256());

    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (int i = 0; i < hash_len + SALT_LENGTH; ++i) {
        printf("%02x", salt[i] < hash_len ? hash[i - hash_len] : salt[i - hash_len]);
    }
    printf("\n");

    // In a real application, here you would store the username, salt, and hashed password in the database.

    return 0;
}


**Note**: This code uses OpenSSL for hashing. You'll need to link against OpenSSL when compiling this code. For example:


gcc -o registration_form registration_form.c -lcrypto