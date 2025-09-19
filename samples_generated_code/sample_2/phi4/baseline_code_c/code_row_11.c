#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

typedef struct {
    char username[50];
    unsigned char hashed_password[32 + SALT_LENGTH]; // SHA-256 hash length + salt
} User;

void generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Error generating random bytes.\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *output_hash) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating MD context.\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing digest.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating digest with password.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) {
        fprintf(stderr, "Error updating digest with salt.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    unsigned int output_len;
    if (1 != EVP_DigestFinal_ex(mdctx, output_hash, &output_len)) {
        fprintf(stderr, "Error finalizing digest.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void register_user(const char *username, const unsigned char *password) {
    User user;
    strncpy(user.username, username, sizeof(user.username));

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, user.hashed_password);

    // Copy the salt to the end of hashed_password
    memcpy(user.hashed_password + 32, salt, SALT_LENGTH);

    printf("User registered:\nUsername: %s\nHashed Password (with Salt): ", user.username);
    for (int i = 0; i < 32 + SALT_LENGTH; ++i) {
        printf("%02x", user.hashed_password[i]);
    }
    printf("\n");

    // Here you would store 'user' in a database
}

void verify_user(const char *username, const unsigned char *password_attempt) {
    User user;
    strncpy(user.username, username, sizeof(user.username));

    // Here you would retrieve the stored hash and salt from the database

    unsigned char salt[SALT_LENGTH];
    memcpy(salt, user.hashed_password + 32, SALT_LENGTH);

    unsigned char hashed_attempt[32];
    hash_password(password_attempt, salt, hashed_attempt);

    if (memcmp(user.hashed_password, hashed_attempt, 32) == 0) {
        printf("Password verification successful.\n");
    } else {
        printf("Password verification failed.\n");
    }
}

int main() {
    const char *username = "testuser";
    const unsigned char password[] = "password123";

    register_user(username, password);

    // Simulate login attempt
    verify_user(username, password);

    return 0;
}