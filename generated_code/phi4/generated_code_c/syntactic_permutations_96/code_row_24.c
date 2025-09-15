#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_OUTPUT_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, 
                  unsigned char *output, size_t output_size) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) return -1;

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1 ||
        EVP_DigestUpdate(ctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestUpdate(ctx, password, strlen((const char *)password)) != 1 ||
        EVP_DigestFinal_ex(ctx, output, (unsigned int *)&output_size) != 1) {
        EVP_MD_CTX_free(ctx);
        return -1;
    }

    EVP_MD_CTX_free(ctx);
    return 0;
}

void store_credentials(const unsigned char *username, const unsigned char *password_hash, 
                       size_t password_hash_size, const unsigned char *salt) {
    // Simulating storage by printing to console (replace with actual database code)
    printf("Storing credentials:\n");
    printf("Username: %s\n", username);
    printf("Password Hash: ");
    for (size_t i = 0; i < password_hash_size; ++i) {
        printf("%02x", password_hash[i]);
    }
    printf("\nSalt: ");
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");
}

int main() {
    unsigned char username[256];
    unsigned char password[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char password_hash[HASH_OUTPUT_SIZE];
    if (hash_password((unsigned char *)password, salt, password_hash, HASH_OUTPUT_SIZE) == -1) {
        fprintf(stderr, "Error hashing password\n");
        return EXIT_FAILURE;
    }

    store_credentials(username, password_hash, sizeof(password_hash), salt);

    return 0;
}
