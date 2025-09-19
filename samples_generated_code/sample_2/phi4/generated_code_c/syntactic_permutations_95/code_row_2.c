#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void handleErrors(void) {
    fprintf(stderr, "An error occurred.\n");
    exit(EXIT_FAILURE);
}

int generateSalt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        handleErrors();
    }
    return 1;
}

int hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char *hash_output) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) handleErrors();

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, password, strlen((const char *)password)) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, salt, SALT_SIZE) != 1) handleErrors();
    unsigned int len = 0;
    if (EVP_DigestFinal_ex(mdctx, hash_output, &len) != 1) handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 1;
}

void storeCredentials(const char *username, const unsigned char *hashed_password_with_salt) {
    // Simulate storing in a database
    printf("Storing credentials for user: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (int i = 0; i < 32 + SALT_SIZE; ++i) {
        printf("%02x", hashed_password_with_salt[i]);
    }
    printf("\n");
}

void registerUser(const char *username, const char *password) {
    unsigned char salt[SALT_SIZE];
    unsigned char hash_output[EVP_MAX_MD_SIZE];

    generateSalt(salt, SALT_SIZE);
    hashPassword((unsigned char *)password, salt, hash_output);

    // Append salt to the hashed password
    unsigned char hashed_password_with_salt[32 + SALT_SIZE];
    memcpy(hashed_password_with_salt, hash_output, 32);
    memcpy(hashed_password_with_salt + 32, salt, SALT_SIZE);

    storeCredentials(username, hashed_password_with_salt);
}

int main() {
    const char *username = "testuser";
    const char *password = "securepassword";

    registerUser(username, password);

    return 0;
}


**Note:** This code requires the OpenSSL library to be installed and linked during compilation. You can compile it with:


gcc -o registration_form registration_form.c -lssl -lcrypto