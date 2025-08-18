#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// OpenSSL libraries for hashing
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, size_t password_len,
                  const unsigned char *salt, size_t salt_size,
                  unsigned char **hashed_out, size_t *hashed_len) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    // Use SHA256
    md = EVP_sha256();

    if ((mdctx = EVP_MD_CTX_new()) == NULL) return 0;

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) return 0;

    if (1 != EVP_DigestUpdate(mdctx, password, password_len)) return 0;
    if (1 != EVP_DigestUpdate(mdctx, salt, salt_size)) return 0;

    if (*hashed_out == NULL) {
        *hashed_len = EVP_MD_size(md);
        *hashed_out = malloc(*hashed_len);
        if (!*hashed_out) return 0;
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_out, hashed_len)) return 0;

    EVP_MD_CTX_free(mdctx);

    return 1;
}

void store_in_database(const char *username, const unsigned char *salt,
                       size_t salt_size, const unsigned char *hashed_password,
                       size_t hashed_password_len) {
    // Simulate storing in database
    printf("Storing user: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < salt_size; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (size_t i = 0; i < hashed_password_len; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    unsigned char salt[SALT_SIZE];
    unsigned char *hashed_password;
    size_t hashed_password_len;

    // Generate random salt
    generate_salt(salt, SALT_SIZE);

    // Get user input
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (hash_password((unsigned char *)password, strlen(password),
                      salt, SALT_SIZE, &hashed_password, &hashed_password_len)) {
        store_in_database(username, salt, SALT_SIZE, hashed_password, hashed_password_len);
    } else {
        fprintf(stderr, "Error hashing password\n");
        return EXIT_FAILURE;
    }

    free(hashed_password);

    return 0;
}