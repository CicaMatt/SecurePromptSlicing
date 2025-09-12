#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include cryptographic library for hashing, such as OpenSSL's EVP library.
#include <openssl/evp.h>
#include <openssl/rand.h>

// Function prototypes
void hashPassword(const char *password, unsigned char **hashedPassword);
int storeCredentials(const char *username, const unsigned char *hashedPassword);

int main() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    scanf("%s", username); // For simplicity, no error checking

    printf("Enter password: ");
    scanf("%s", password); // For simplicity, no error checking

    unsigned char *hashedPassword = NULL;
    hashPassword(password, &hashedPassword);

    if (storeCredentials(username, hashedPassword) != 0) {
        fprintf(stderr, "Error storing credentials\n");
        return 1;
    }

    printf("Registration successful!\n");

    // Free the allocated memory for the hashed password
    OPENSSL_free(hashedPassword);
    
    return 0;
}

void hashPassword(const char *password, unsigned char **hashedPassword) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    int md_len, data_len = strlen(password);

    // Select hashing algorithm
    if (1 != OpenSSL_add_all_digests()) {
        fprintf(stderr, "Error adding all digests\n");
        exit(1);
    }
    md = EVP_sha256(); // Using SHA-256 for example

    // Create and initialize the context
    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "EVP_MD_CTX_new failed\n");
        exit(1);
    }

    // Perform hashing
    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Digest initialization failed\n");
        exit(1);
    }
    if (1 != EVP_DigestUpdate(mdctx, password, data_len)) {
        fprintf(stderr, "Digest update failed\n");
        exit(1);
    }

    // Determine the length of the hash
    if (NULL == (md_len = EVP_MD_size(md))) {
        fprintf(stderr, "EVP_MD_size failed\n");
        exit(1);
    }
    
    *hashedPassword = (unsigned char *)OPENSSL_malloc(md_len);
    if (*hashedPassword == NULL) {
        fprintf(stderr, "Memory allocation for hashed password failed\n");
        exit(1);
    }

    // Finalize the hash
    if (1 != EVP_DigestFinal_ex(mdctx, *hashedPassword, &md_len)) {
        fprintf(stderr, "Digest finalization failed\n");
        exit(1);
    }
    
    // Clean up
    EVP_MD_CTX_free(mdctx);
}

int storeCredentials(const char *username, const unsigned char *hashedPassword) {
    // Dummy function to simulate storing credentials in a database
    printf("Storing user: %s with hashed password of length %lu\n", username, strlen((char *)hashedPassword));

    return 0; // Return 0 on success, non-zero on failure
}


**Note**: This code uses OpenSSL for hashing the password and assumes you have OpenSSL installed. For a real application, make sure to handle errors more gracefully and securely manage user input.