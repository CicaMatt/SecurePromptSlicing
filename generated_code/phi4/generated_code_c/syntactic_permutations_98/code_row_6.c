#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT_SIZE 256

// Function to hash a string using SHA-256
void hash_password(const unsigned char *message, size_t message_len, unsigned char *digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    OpenSSL_add_all_digests();
    md = EVP_sha256();

    if(!(mdctx = EVP_MD_CTX_new())) {
        exit(1);
    }

    if(1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        exit(2);
    }

    if(1 != EVP_DigestUpdate(mdctx, message, message_len)) {
        exit(3);
    }

    if(1 != EVP_DigestFinal_ex(mdctx, digest, NULL)) {
        exit(4);
    }

    EVP_MD_CTX_free(mdctx);
}

// Simulated database insert function
void insert_into_database(const char *username, const unsigned char *hashed_password) {
    // This is a placeholder for actual database interaction code.
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for(int i = 0; i < EVP_MD_size(EVP_sha256()); ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];
    unsigned char digest[EVP_MAX_MD_SIZE];

    printf("Enter username: ");
    if (fgets(username, MAX_INPUT_SIZE, stdin) == NULL || strlen(username) > 0 && username[strlen(username) - 1] == '\n') {
        username[strlen(username) - 1] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, MAX_INPUT_SIZE, stdin) == NULL || strlen(password) > 0 && password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0';
    }

    hash_password((unsigned char *)password, strlen(password), digest);

    insert_into_database(username, digest);

    return 0;
}