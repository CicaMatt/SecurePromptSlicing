#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(unsigned char *salt, int length) {
    if (!RAND_bytes(salt, length)) {
        fprintf(stderr, "Failed to generate random salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash, int hash_length) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    if ((mdctx = EVP_MD_CTX_create()) == NULL) {
        fprintf(stderr, "Failed to create EVP_MD_CTX\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Failed in EVP_DigestInit_ex\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) {
        fprintf(stderr, "Failed in EVP_DigestUpdate with salt\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        fprintf(stderr, "Failed in EVP_DigestUpdate with password\n");
        exit(EXIT_FAILURE);
    }

    unsigned int digest_len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &digest_len)) {
        fprintf(stderr, "Failed in EVP_DigestFinal_ex\n");
        exit(EXIT_FAILURE);
    }

    if (hash_length < digest_len) {
        fprintf(stderr, "Hash buffer is too small\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_destroy(mdctx);
}

void store_in_database(const char *username, const unsigned char *salt, const unsigned char *hashed_password, int hash_length) {
    // This function should implement the logic to store username, salt, and hashed password in a database.
    // For demonstration purposes, we'll just print them out.
    printf("Storing user data:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < hash_length; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Failed to read username\n");
        exit(EXIT_FAILURE);
    }
    // Remove newline character from username
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Failed to read password\n");
        exit(EXIT_FAILURE);
    }
    // Remove newline character from password
    password[strcspn(password, "\n")] = '\0';

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    unsigned char hashed_password[EVP_MAX_MD_SIZE]; // This will hold the hash value
    int hash_length = EVP_MD_size(EVP_sha256());

    hash_password((unsigned char *)password, salt, hashed_password, hash_length);

    store_in_database(username, salt, hashed_password, hash_length);

    return 0;
}