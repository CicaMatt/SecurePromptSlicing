#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating EVP_MD_CTX\n");
        exit(EXIT_FAILURE);
    }

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) <= 0 ||
        EVP_DigestUpdate(mdctx, password, strlen((char *)password)) <= 0 ||
        EVP_DigestUpdate(mdctx, salt, SALT_SIZE) <= 0 ||
        EVP_DigestFinal_ex(mdctx, hash, NULL) <= 0) {
        fprintf(stderr, "Error hashing the password\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void store_credentials(const char *username, const unsigned char *salt, const unsigned char *hash) {
    FILE *file = fopen("credentials.db", "a");
    if (!file) {
        fprintf(stderr, "Error opening credentials file\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %.*s %.*s\n",
            username,
            SALT_SIZE, (const char *)salt,
            HASH_SIZE, (const char *)hash);

    fclose(file);
}

int main() {
    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];

    printf("Enter username: ");
    char username[256];
    scanf("%255s", username);

    printf("Enter password: ");
    char password[256];
    scanf("%255s", password);

    hash_password((unsigned char *)password, salt, hash);
    store_credentials(username, salt, hash);

    printf("Registration successful!\n");
    
    return 0;
}
