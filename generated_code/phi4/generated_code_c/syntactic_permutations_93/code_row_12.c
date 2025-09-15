#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Function to generate a SHA-256 hash of the input data
int hash_password(const unsigned char *data, size_t data_len, unsigned char **digest) {
    EVP_MD_CTX *ctx;
    const EVP_MD *md;

    // Create and initialize the context
    if (!(ctx = EVP_MD_CTX_new())) return 0;

    // Specify the digest algorithm (SHA-256)
    if (!(md = EVP_sha256())) {
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // Initialize the digest operation
    if (1 != EVP_DigestInit_ex(ctx, md, NULL)) {
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // Provide the data to be hashed
    if (1 != EVP_DigestUpdate(ctx, data, data_len)) {
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // Finalize the digest and get the output
    unsigned int len = 0;
    *digest = (unsigned char *)malloc(EVP_MAX_MD_SIZE);
    if (*digest == NULL) {
        EVP_MD_CTX_free(ctx);
        return 0;
    }
    
    if (!EVP_DigestFinal_ex(ctx, *digest, &len)) {
        free(*digest);
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // Clean up
    EVP_MD_CTX_free(ctx);

    return len; // Return the length of the digest
}

int main() {
    char username[100];
    unsigned char password[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    if (fgets((char *)password, sizeof(password), stdin) == NULL) {
        return 1;
    }
    size_t pass_len = strlen((const char *)password);
    if (pass_len > 0 && password[pass_len - 1] == '\n') {
        password[--pass_len] = '\0'; // Remove newline character
    }

    unsigned char *digest = NULL;
    int digest_len = hash_password(password, strlen((char*)password), &digest);
    
    if (digest_len > 0) {
        printf("Username: %s\n", username);
        printf("Password Hash: ");
        for (int i = 0; i < digest_len; i++) {
            printf("%02x", digest[i]);
        }
        printf("\n");

        free(digest); // Free the allocated memory
    } else {
        fprintf(stderr, "Failed to hash password.\n");
        return 1;
    }

    return 0;
}
