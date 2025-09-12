#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_len) {
    if (RAND_bytes(salt, salt_len) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_password, size_t *hashed_password_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    unsigned int md_len;

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        fprintf(stderr, "Error updating digest with password\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt\n");
        exit(EXIT_FAILURE);
    }

    *hashed_password = malloc(EVP_MD_size(md));
    if (*hashed_password == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_password, &md_len)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(EXIT_FAILURE);
    }

    *hashed_password_len = md_len;
    EVP_MD_CTX_free(mdctx);
}

void store_user(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    // Simulate storing in a database
    printf("Storing user '%s' with salt and hashed password...\n", username);

    printf("Salt: ");
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (size_t i = 0; i < EVP_MD_size(EVP_sha256()); ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[50];
    char password[50];

    unsigned char salt[SALT_SIZE];
    unsigned char *hashed_password;
    size_t hashed_password_len;

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char *)password, salt, &hashed_password, &hashed_password_len);
    store_user(username, salt, hashed_password);

    free(hashed_password);
    return 0;
}