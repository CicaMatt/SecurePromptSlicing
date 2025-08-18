#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

// Function prototypes
void hash_password(const char *password, unsigned char **hash, unsigned int *hash_len);
int generate_salt(unsigned char *salt, size_t salt_length);

// Database simulation
typedef struct {
    char username[50];
    unsigned char password_hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[SALT_LENGTH + 1]; // Salt length + null terminator for storage
} User;

User database[10]; // Simulated small user database

int main() {
    const char *username;
    char password[100];
    
    printf("Enter username: ");
    scanf("%49s", username); // Limit input to avoid buffer overflow
    
    printf("Enter password: ");
    scanf("%99s", password);
    
    unsigned char *hash = NULL;
    unsigned int hash_len;
    unsigned char salt[SALT_LENGTH + 1]; // Extra byte for null terminator

    if (generate_salt(salt, SALT_LENGTH) != 0) {
        fprintf(stderr, "Failed to generate salt.\n");
        return 1;
    }
    
    hash_password(password, &hash, &hash_len);
    
    User newUser;
    strncpy(newUser.username, username, sizeof(newUser.username));
    memcpy(newUser.password_hash, hash, hash_len);
    memcpy(newUser.salt, salt, SALT_LENGTH + 1); // Copy the null terminator too

    printf("User registered successfully!\n");

    free(hash);

    return 0;
}

void hash_password(const char *password, unsigned char **hash, unsigned int *hash_len) {
    EVP_MD_CTX *mdctx = NULL;

    if (!(*hash = malloc(EVP_MAX_MD_SIZE))) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    if (!(mdctx = EVP_MD_CTX_new())) {
        free(*hash);
        fprintf(stderr, "Could not create MD context.\n");
        exit(1);
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        EVP_MD_CTX_free(mdctx);
        free(*hash);
        fprintf(stderr, "Hash initialization failed.\n");
        exit(1);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        EVP_MD_CTX_free(mdctx);
        free(*hash);
        fprintf(stderr, "Hash update failed.\n");
        exit(1);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hash, hash_len)) {
        EVP_MD_CTX_free(mdctx);
        free(*hash);
        fprintf(stderr, "Hash finalization failed.\n");
        exit(1);
    }
    
    EVP_MD_CTX_free(mdctx);
}

int generate_salt(unsigned char *salt, size_t salt_length) {
    if (RAND_bytes(salt, salt_length) != 1) {
        return -1;
    }

    salt[salt_length] = '\0'; // Null-terminate the salt
    return 0;
}