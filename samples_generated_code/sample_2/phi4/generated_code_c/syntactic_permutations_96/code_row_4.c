#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_MD_fetch(NULL, "SHA256", NULL) <= 0) {
        fprintf(stderr, "Could not fetch SHA-256 algorithm\n");
        return -1;
    }

    md = EVP_get_digestbyname("sha256");

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating message digest context\n");
        return -1;
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) <= 0 ||
        EVP_DigestUpdate(mdctx, password, strlen((char *)password)) <= 0 ||
        EVP_DigestUpdate(mdctx, salt, SALT_SIZE) <= 0 ||
        EVP_DigestFinal_ex(mdctx, output, NULL) <= 0) {
        fprintf(stderr, "Error hashing password\n");
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    EVP_MD_CTX_free(mdctx);

    return 0;
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    printf("Storing credentials for user: %s\n", username);
    // For demonstration, we are printing the salted hash.
    // In a real application, you would store it in a database.
    printf("Salted Hash: ");
    for (int i = 0; i < HASH_SIZE + SALT_SIZE; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

void register_user() {
    char username[256];
    unsigned char password[256], salt[SALT_SIZE], hash[HASH_SIZE], salted_hash[HASH_SIZE + SALT_SIZE];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_SIZE);

    if (hash_password(password, salt, hash) == 0) {
        memcpy(salted_hash, salt, SALT_SIZE);
        memcpy(salted_hash + SALT_SIZE, hash, HASH_SIZE);
        store_credentials(username, salted_hash);
    } else {
        fprintf(stderr, "Failed to hash password\n");
    }
}

int main() {
    register_user();
    return 0;
}