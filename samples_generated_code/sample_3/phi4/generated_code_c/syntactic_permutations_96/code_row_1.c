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

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    int md_len;

    if (!(mdctx = EVP_MD_CTX_new())) {
        fprintf(stderr, "Error creating MD context\n");
        return 0;
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating digest\n");
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt\n");
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    unsigned char md_temp[EVP_MAX_MD_SIZE];
    if (1 != EVP_DigestFinal_ex(mdctx, md_temp, &md_len)) {
        fprintf(stderr, "Error finalizing digest\n");
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    memcpy(hash, md_temp, md_len);
    EVP_MD_CTX_free(mdctx);

    return 1;
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // This is a placeholder for storing the credentials in a database.
    // In a real application, you would replace this with actual database code.
    printf("Storing username: %s\n", username);
    printf("Storing salted hash:\n");
    for (int i = 0; i < HASH_SIZE + SALT_SIZE; i++) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];
    unsigned char salted_hash[HASH_SIZE + SALT_SIZE];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0'; // Remove newline
    }

    generate_salt(salt, SALT_SIZE);

    if (!hash_password((unsigned char *)password, salt, hash)) {
        fprintf(stderr, "Error hashing password\n");
        return EXIT_FAILURE;
    }

    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, hash, HASH_SIZE);

    store_credentials(username, salted_hash);

    return 0;
}