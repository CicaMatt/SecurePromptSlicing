#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(unsigned char *salt, size_t length) {
    if (!RAND_bytes(salt, length)) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt,
                  unsigned char *hash_output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    if (!(mdctx = EVP_MD_CTX_create())) {
        fprintf(stderr, "EVP_MD_CTX_create failed\n");
        return 0;
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "EVP_DigestInit_ex failed\n");
        goto err;
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) {
        fprintf(stderr) << "EVP_DigestUpdate failed for salt" << std::endl;
        goto err;
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        fprintf(stderr) << "EVP_DigestUpdate failed for password" << std::endl;
        goto err;
    }

    unsigned int hash_len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash_output, &hash_len)) {
        fprintf(stderr) << "EVP_DigestFinal_ex failed" << std::endl;
        goto err;
    }

    EVP_MD_CTX_destroy(mdctx);
    return 1;

err:
    EVP_MD_CTX_destroy(mdctx);
    return 0;
}

int main() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    if (!fgets(username, sizeof(username), stdin) || strlen(username) == 0 ||
        username[strlen(username) - 1] == '\n') {
        fprintf(stderr, "Invalid input for username\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (!fgets(password, sizeof(password), stdin) || strlen(password) == 0 ||
        password[strlen(password) - 1] == '\n') {
        fprintf(stderr, "Invalid input for password\n");
        return EXIT_FAILURE;
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    unsigned char hash_output[HASH_LENGTH];
    if (!hash_password((unsigned char *)password, salt, hash_output)) {
        fprintf(stderr, "Password hashing failed\n");
        return EXIT_FAILURE;
    }

    printf("Username: %s\n", username);
    printf("Salt (hex): ");
    for (size_t i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password (hex): ");
    for (size_t i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}