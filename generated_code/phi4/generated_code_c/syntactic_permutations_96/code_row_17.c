#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) return 0;

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1)
        goto err;

    if (EVP_DigestUpdate(mdctx, salt, SALT_LENGTH) != 1)
        goto err;

    if (EVP_DigestUpdate(mdctx, password, strlen((char *)password)) != 1)
        goto err;

    unsigned int md_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &md_len) != 1)
        goto err;

    EVP_MD_CTX_free(mdctx);
    return 1;

err:
    EVP_MD_CTX_free(mdctx);
    return 0;
}

void store_credentials(const char *username, const unsigned char *salted_hash, size_t length) {
    // Placeholder for storing credentials in a database
    printf("Storing user: %s\n", username);
    printf("Salted Hash (hex): ");
    for (size_t i = 0; i < length; i++) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    generate_salt(salt, SALT_LENGTH);

    const char *username = "user123";
    const char *password = "secure_password";

    if (hash_password((unsigned char *)password, salt, hash) == 0) {
        fprintf(stderr, "Error hashing password\n");
        return EXIT_FAILURE;
    }

    unsigned char salted_hash[SALT_LENGTH + HASH_LENGTH];
    memcpy(salted_hash, salt, SALT_LENGTH);
    memcpy(salted_hash + SALT_LENGTH, hash, HASH_LENGTH);

    store_credentials(username, salted_hash, SALT_LENGTH + HASH_LENGTH);

    return 0;
}
