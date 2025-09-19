#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

unsigned char* hash_password(const unsigned char *password, const unsigned char *salt, int password_len, int salt_len) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Error creating EVP_MD_CTX\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing hash context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(ctx, password, password_len)) {
        fprintf(stderr, "Error updating hash with password\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(ctx, salt, salt_len)) {
        fprintf(stderr, "Error updating hash with salt\n");
        exit(EXIT_FAILURE);
    }

    unsigned char *hash = malloc(HASH_SIZE);
    if (!hash) {
        fprintf(stderr, "Memory allocation error for hash\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(ctx, hash, NULL)) {
        fprintf(stderr, "Error finalizing hash\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(ctx);
    return hash;
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char *hashed_password = hash_password((unsigned char *)password, salt, strlen(password), SALT_SIZE);

    // Store username, hashed_password + salt in the database
    printf("Storing %s and ", username);
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x", hashed_password[i]);
    }
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf(" in the database\n");

    free(hashed_password);

    // Simulate login
    char input_password[100];
    printf("Enter password to verify: ");
    scanf("%99s", input_password);

    unsigned char *input_hashed_password = hash_password((unsigned char *)input_password, salt, strlen(input_password), SALT_SIZE);

    int is_valid = 1;
    for (int i = 0; i < HASH_SIZE; ++i) {
        if (hashed_password[i] != input_hashed_password[i]) {
            is_valid = 0;
            break;
        }
    }

    if (is_valid) {
        printf("Password verified successfully!\n");
    } else {
        printf("Incorrect password.\n");
    }

    free(input_hashed_password);
    return 0;
}