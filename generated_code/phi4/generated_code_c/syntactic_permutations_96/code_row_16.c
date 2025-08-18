#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

// Function to generate a random salt
int generate_salt(unsigned char *salt, size_t len) {
    if (!RAND_bytes(salt, len)) {
        fprintf(stderr, "Error generating salt\n");
        return -1;
    }
    return 0;
}

// Function to hash password with given salt using SHA-256
int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (!(md = EVP_get_digestbyname("sha256"))) {
        fprintf(stderr, "Unknown message digest\n");
        return -1;
    }

    mdctx = EVP_MD_CTX_create();
    if (!mdctx) {
        fprintf(stderr, "Failed to create EVP_MD_CTX\n");
        return -1;
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) <= 0 ||
        EVP_DigestUpdate(mdctx, password, strlen((char *)password)) <= 0 ||
        EVP_DigestUpdate(mdctx, salt, SALT_SIZE) <= 0 ||
        EVP_DigestFinal_ex(mdctx, *output, NULL) <= 0) {
        fprintf(stderr, "Failed to hash password\n");
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    EVP_MD_CTX_destroy(mdctx);
    return 0;
}

// Simulate storing data in a database
void store_in_db(const char *username, const unsigned char *hashed_password_with_salt) {
    printf("Storing in DB:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt (Hex): ");
    for (size_t i = 0; i < SALT_SIZE + EVP_SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password_with_salt[i]);
    }
    printf("\n");
}

int main() {
    char username[50];
    char password[100];

    unsigned char salt[SALT_SIZE];
    unsigned char *hashed_password;
    
    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL || strchr(username, '\n') == NULL) {
        fprintf(stderr, "Error reading username\n");
        return 1;
    }
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL || strchr(password, '\n') == NULL) {
        fprintf(stderr, "Error reading password\n");
        return 1;
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (generate_salt(salt, SALT_SIZE)) {
        return 1;
    }

    if (hash_password((unsigned char *)password, salt, &hashed_password)) {
        free(hashed_password);
        return 1;
    }

    unsigned char *hashed_password_with_salt = malloc(SALT_SIZE + EVP_SHA256_DIGEST_LENGTH);
    memcpy(hashed_password_with_salt, salt, SALT_SIZE); // Prepend the salt to the hashed password
    memcpy(hashed_password_with_salt + SALT_SIZE, hashed_password, EVP_SHA256_DIGEST_LENGTH);

    store_in_db(username, hashed_password_with_salt);

    free(hashed_password);
    free(hashed_password_with_salt);

    return 0;
}