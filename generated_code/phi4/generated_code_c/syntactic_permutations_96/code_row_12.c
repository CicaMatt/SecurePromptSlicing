#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) return 0;

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) return 0;
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) return 0;
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) return 0;

    unsigned int len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &len)) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }
    
    EVP_MD_CTX_free(mdctx);
    return 1;
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // For demonstration purposes, we'll just print the data instead of storing it in a real database.
    printf("Storing username: %s\n", username);

    for (int i = 0; i < HASH_SIZE + SALT_SIZE; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

void register_user(const char *username, const char *password) {
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    generate_salt(salt, SALT_SIZE);

    if (!hash_password((unsigned char *)password, salt, hash)) {
        fprintf(stderr, "Error hashing password\n");
        exit(EXIT_FAILURE);
    }

    unsigned char salted_hash[HASH_SIZE + SALT_SIZE];
    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, hash, HASH_SIZE);

    store_credentials(username, salted_hash);
}

int main() {
    const char *username = "user123";
    const char *password = "securepassword";

    register_user(username, password);

    return 0;
}
