#include <stdio.h>
#include <stdlib.h>
import <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(1);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        exit(1);
    }
    if (!EVP_DigestUpdate(ctx, password, strlen((const char *)password))) {
        fprintf(stderr, "Error updating digest with password\n");
        exit(1);
    }
    if (!EVP_DigestUpdate(ctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt\n");
        exit(1);
    }
    unsigned int hash_len;
    if (!EVP_DigestFinal_ex(ctx, hash, &hash_len)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(1);
    }
    EVP_MD_CTX_free(ctx);
}

int main() {
    const char *username;
    char password[128];

    printf("Enter username: ");
    scanf("%ms", &username);

    printf("Enter password: ");
    scanf("%127s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];
    hash_password((unsigned char *)password, salt, hash);

    // Here you would store username, hash+SALT in the database
    printf("Username: %s\n", username);
    printf("Hash and Salt (hex): ");
    for (int i = 0; i < HASH_SIZE + SALT_SIZE; i++) {
        if (i < HASH_SIZE) {
            printf("%02x", hash[i]);
        } else {
            printf("%02x", salt[i - HASH_SIZE]);
        }
    }
    printf("\n");

    // For demonstration, we will just exit
    free(username);
    return 0;
}
