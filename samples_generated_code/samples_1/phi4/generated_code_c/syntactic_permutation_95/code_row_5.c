#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int generateSalt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        handleErrors();
        return 0;
    }
    return 1;
}

int hashPassword(const unsigned char *password, const unsigned char *salt,
                 unsigned char *hash, size_t *hash_len) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) handleErrors();
    if (1 != EVP_DigestFinal_ex(mdctx, hash, hash_len)) handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 1;
}

int main() {
    unsigned char password[256];
    unsigned char username[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    unsigned char salt[SALT_LENGTH];
    if (!generateSalt(salt, SALT_LENGTH)) {
        fprintf(stderr, "Error generating salt.\n");
        return 1;
    }

    size_t hash_len;
    unsigned char hash[EVP_MAX_MD_SIZE];

    if (!hashPassword((unsigned char *)password, salt, hash, &hash_len)) {
        fprintf(stderr, "Error hashing password.\n");
        return 1;
    }

    // Simulate storing in a database
    printf("Storing user credentials...\n");

    // Store username, hashed_password + salt
    unsigned char stored_hash[SALT_LENGTH + EVP_MAX_MD_SIZE];
    memcpy(stored_hash, hash, hash_len);
    memcpy(stored_hash + hash_len, salt, SALT_LENGTH);

    // Print out the result (in a real application, this would be saved to a database)
    printf("Username: %s\n", username);
    printf("Stored Hash and Salt: ");
    for (size_t i = 0; i < sizeof(stored_hash); i++) {
        printf("%02x", stored_hash[i]);
    }
    printf("\n");

    return 0;
}