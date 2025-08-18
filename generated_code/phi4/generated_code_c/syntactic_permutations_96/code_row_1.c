#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(unsigned char *salt, size_t length) {
    if (!RAND_bytes(salt, length)) {
        fprintf(stderr, "Error generating salt.\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating EVP_MD_CTX.\n");
        return -1;
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1 ||
        EVP_DigestUpdate(mdctx, password, strlen((const char *)password)) != 1 ||
        EVP_DigestUpdate(mdctx, salt, SALT_LENGTH) != 1 ||
        EVP_DigestFinal_ex(mdctx, *hashed_password, NULL) != 1) {
        fprintf(stderr, "Error hashing password.\n");
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    EVP_MD_CTX_free(mdctx);
    return 0;
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // Simulate storing in a database
    printf("Storing credentials for user: %s\n", username);
    for (int i = 0; i < HASH_LENGTH + SALT_LENGTH; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    unsigned char password[100];
    unsigned char *hashed_password;
    unsigned char salt[SALT_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    hashed_password = malloc(HASH_LENGTH + 1); // Allocate memory for the hash
    if (hashed_password == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (hash_password((unsigned char *)password, salt, &hashed_password) != 0) {
        free(hashed_password);
        return EXIT_FAILURE;
    }

    unsigned char *salted_hash = malloc(HASH_LENGTH + SALT_LENGTH);
    if (salted_hash == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(hashed_password);
        return EXIT_FAILURE;
    }

    memcpy(salted_hash, salt, SALT_LENGTH);
    memcpy(salted_hash + SALT_LENGTH, hashed_password, HASH_LENGTH);

    store_credentials(username, salted_hash);

    free(hashed_password);
    free(salted_hash);

    return EXIT_SUCCESS;
}