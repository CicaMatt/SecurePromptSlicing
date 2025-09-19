#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Function to generate a random salt
void generate_salt(unsigned char *salt, size_t length) {
    if (!RAND_bytes(salt, length)) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

// Function to hash the password with salt using SHA-256
void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();

    if (!(mdctx = EVP_MD_CTX_new())) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        exit(EXIT_FAILURE);
    }

    // Concatenate password and salt
    size_t total_length = strlen((char *)password) + EVP_MD_size(md);
    unsigned char *data_to_hash = malloc(total_length);

    if (!data_to_hash) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(data_to_hash, password, strlen((char *)password));
    memcpy(data_to_hash + strlen((char *)password), salt, EVP_MD_size(md));

    if (1 != EVP_DigestUpdate(mdctx, data_to_hash, total_length)) {
        fprintf(stderr, "Error updating digest\n");
        exit(EXIT_FAILURE);
    }

    unsigned int md_len;
    *hashed_output = malloc(EVP_MAX_MD_SIZE);

    if (!*hashed_output) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_output, &md_len)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(EXIT_FAILURE);
    }

    free(data_to_hash);
    EVP_MD_CTX_free(mdctx);
}

// Simulate storing the salt and hashed password in a database
void store_credentials(const unsigned char *username, const unsigned char *salt, size_t salt_length, const unsigned char *hashed_password) {
    printf("Storing credentials for user: %s\n", username);

    printf("Salt: ");
    for (size_t i = 0; i < salt_length; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (unsigned int i = 0; i < EVP_MD_size(EVP_sha256()); i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    const char *username;
    unsigned char password[256];
    unsigned char salt[EVP_MAX_MD_SIZE];
    unsigned char *hashed_password;

    printf("Enter username: ");
    scanf("%ms", &username);

    printf("Enter password: ");
    scanf("%255s", (char *)password);

    generate_salt(salt, EVP_MAX_MD_SIZE);
    hash_password(password, salt, &hashed_password);
    store_credentials(username, salt, EVP_MAX_MD_SIZE, hashed_password);

    free(hashed_password);
    return 0;
}