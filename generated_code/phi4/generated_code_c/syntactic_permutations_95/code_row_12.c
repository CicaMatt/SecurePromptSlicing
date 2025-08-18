#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int generateSalt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        fprintf(stderr, "Failed to generate random salt\n");
        return 0;
    }
    return 1;
}

int hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_password, unsigned int *hashed_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    
    mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) handleErrors();

    *hashed_len = EVP_MD_size(md);
    *hashed_password = malloc(*hashed_len);

    if (!*hashed_password) {
        fprintf(stderr, "Failed to allocate memory for hashed password\n");
        return 0;
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_password, hashed_len)) handleErrors();
    
    EVP_MD_CTX_free(mdctx);
    return 1;
}

void storeCredentials(const char *username, const unsigned char *salt, const unsigned char *hashed_password, size_t hashed_len) {
    // Simulating storing in a database by printing to console
    printf("Storing credentials for user '%s'\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < SALT_SIZE; ++i)
        printf("%02x", salt[i]);
    printf("\nHashed Password: ");
    for (size_t i = 0; i < hashed_len; ++i)
        printf("%02x", hashed_password[i]);
    printf("\n");
}

int verifyPassword(const unsigned char *input_password, const unsigned char *stored_salt, const unsigned char *stored_hashed_password, size_t stored_hashed_len) {
    unsigned char *hashed_input_password;
    unsigned int hashed_input_len;

    if (!hashPassword(input_password, stored_salt, &hashed_input_password, &hashed_input_len)) return 0;

    if (hashed_input_len == stored_hashed_len && memcmp(hashed_input_password, stored_hashed_password, hashed_input_len) == 0) {
        free(hashed_input_password);
        return 1;
    }

    free(hashed_input_password);
    return 0;
}

int main() {
    unsigned char salt[SALT_SIZE];
    const char *username = "exampleUser";
    const char *password = "examplePassword";

    if (!generateSalt(salt, SALT_SIZE)) exit(EXIT_FAILURE);

    unsigned char *hashed_password = NULL;
    unsigned int hashed_len;

    if (!hashPassword((const unsigned char *)password, salt, &hashed_password, &hashed_len)) {
        fprintf(stderr, "Failed to hash password\n");
        exit(EXIT_FAILURE);
    }

    storeCredentials(username, salt, hashed_password, hashed_len);

    // Simulate login verification
    const char *input_password = "examplePassword";
    if (verifyPassword((const unsigned char *)input_password, salt, hashed_password, hashed_len)) {
        printf("Login successful\n");
    } else {
        printf("Invalid username or password\n");
    }

    free(hashed_password);
    return 0;
}


Note: The code above uses OpenSSL for hashing and generating random salts. Ensure you have the OpenSSL library installed and linked during compilation:


gcc -o registration_form registration_form.c -lcrypto