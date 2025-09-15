#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash, size_t *hash_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1 ||
        EVP_DigestUpdate(mdctx, password, strlen((char *)password)) != 1 ||
        EVP_DigestUpdate(mdctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestFinal_ex(mdctx, hash, hash_len) != 1) {
        fprintf(stderr, "Error hashing password\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void store_credentials(const char *username, const unsigned char *hashed_password_with_salt, size_t length) {
    // This is a placeholder for storing credentials in the database
    printf("Storing username: %s\n", username);
    printf("Hashed password with salt (hex): ");
    for (size_t i = 0; i < length; ++i) {
        printf("%02x", hashed_password_with_salt[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];
    size_t hash_len;

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char *)password, salt, hash, &hash_len);

    unsigned char hashed_password_with_salt[hash_len + SALT_SIZE];
    memcpy(hashed_password_with_salt, hash, hash_len);
    memcpy(hashed_password_with_salt + hash_len, salt, SALT_SIZE);

    store_credentials(username, hashed_password_with_salt, hash_len + SALT_SIZE);

    return 0;
}
