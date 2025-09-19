#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_password, size_t *hashed_size) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Error creating context for hashing\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) {
        EVP_MD_CTX_free(ctx);
        fprintf(stderr, "Error initializing hash function\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(ctx, password, strlen((char *)password))) {
        EVP_MD_CTX_free(ctx);
        fprintf(stderr, "Error updating digest with password\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(ctx, salt, SALT_SIZE)) {
        EVP_MD_CTX_free(ctx);
        fprintf(stderr, "Error updating digest with salt\n");
        exit(EXIT_FAILURE);
    }

    *hashed_size = EVP_MAX_MD_SIZE;
    *hashed_password = malloc(*hashed_size);

    if (!*hashed_password) {
        EVP_MD_CTX_free(ctx);
        fprintf(stderr, "Memory allocation error for hashed password\n");
        exit(EXIT_FAILURE);
    }

    int length = 0;
    if (1 != EVP_DigestFinal_ex(ctx, *hashed_password, &length)) {
        free(*hashed_password);
        EVP_MD_CTX_free(ctx);
        fprintf(stderr, "Error finalizing hash function\n");
        exit(EXIT_FAILURE);
    }
    
    EVP_MD_CTX_free(ctx);

    // Resize the buffer to actual hashed size
    unsigned char *temp = realloc(*hashed_password, length);
    if (!temp) {
        free(*hashed_password);
        fprintf(stderr, "Memory reallocation error for hashed password\n");
        exit(EXIT_FAILURE);
    }
    *hashed_password = temp;
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_SIZE);
    
    unsigned char *hashed_password;
    size_t hashed_size;

    hash_password((unsigned char *)password, salt, &hashed_password, &hashed_size);

    // Concatenate salt and hashed password for storage
    size_t storage_size = SALT_SIZE + hashed_size;
    unsigned char *stored_data = malloc(storage_size);
    
    if (!stored_data) {
        free(hashed_password);
        fprintf(stderr, "Memory allocation error for stored data\n");
        exit(EXIT_FAILURE);
    }

    memcpy(stored_data, salt, SALT_SIZE);
    memcpy(stored_data + SALT_SIZE, hashed_password, hashed_size);

    // Here you would store `stored_data` in your database
    printf("Username: %s\n", username);
    printf("Stored Data (Salt + Hash): ");
    for (size_t i = 0; i < storage_size; ++i) {
        printf("%02x", stored_data[i]);
    }
    printf("\n");

    free(hashed_password);
    free(stored_data);

    return 0;
}