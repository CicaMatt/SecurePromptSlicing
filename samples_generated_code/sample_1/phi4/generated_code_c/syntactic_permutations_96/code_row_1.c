#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_md5() == NULL) {
        fprintf(stderr, "Error: EVP_md5 is not available.\n");
        return 0;
    }

    md = EVP_md5();
    if ((mdctx = EVP_MD_CTX_new()) == NULL) {
        fprintf(stderr, "Error: EVP_MD_CTX_new failed\n");
        return 0;
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) <= 0) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (EVP_DigestUpdate(mdctx, password, strlen((char *)password)) <= 0 ||
        EVP_DigestUpdate(mdctx, salt, SALT_SIZE) <= 0) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    unsigned int md_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &md_len) <= 0) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }
    EVP_MD_CTX_free(mdctx);

    return 1;
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // Simulate storing the credentials in a database
    printf("Storing credentials for user: %s\n", username);
    printf("Salted Hash: ");
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

void register_user(const char *username, const char *password) {
    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];
    if (!hash_password((unsigned char *)password, salt, hash)) {
        fprintf(stderr, "Error hashing password\n");
        exit(EXIT_FAILURE);
    }

    unsigned char *salted_hash = malloc(SALT_SIZE + HASH_SIZE);
    if (salted_hash == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, hash, HASH_SIZE);

    store_credentials(username, salted_hash);
    free(salted_hash);
}

int main() {
    const char *username = "test_user";
    const char *password = "secure_password123";

    register_user(username, password);

    return 0;
}