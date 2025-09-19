#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASHED_PASSWORD_SIZE 32

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes.\n");
        exit(1);
    }
}

int hash_password(const unsigned char *password, size_t password_len, 
                  const unsigned char *salt, unsigned char **hashed_password) {
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        fprintf(stderr, "Error creating MD context.\n");
        return 0;
    }

    if (EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL) != 1 ||
        EVP_DigestUpdate(md_ctx, password, password_len) != 1 ||
        EVP_DigestUpdate(md_ctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestFinal_ex(md_ctx, *hashed_password, NULL) != 1) {
        fprintf(stderr, "Error hashing password.\n");
        EVP_MD_CTX_free(md_ctx);
        return 0;
    }

    EVP_MD_CTX_free(md_ctx);
    return 1;
}

int store_credentials(const char *username, const unsigned char *salt, 
                      const unsigned char *hashed_password) {
    // This is a placeholder for actual database storage logic.
    printf("Storing credentials:\n");
    printf("Username: %s\n", username);

    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (int i = 0; i < HASHED_PASSWORD_SIZE; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 1;
}

void register_user() {
    char username[256];
    unsigned char password[256];
    unsigned char salt[SALT_SIZE];
    unsigned char *hashed_password = malloc(HASHED_PASSWORD_SIZE);

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", (char *)password);

    generate_salt(salt, SALT_SIZE);

    if (!hash_password((unsigned char *)password, strlen((char *)password), salt, &hashed_password)) {
        free(hashed_password);
        return;
    }

    if (!store_credentials(username, salt, hashed_password)) {
        free(hashed_password);
        return;
    }

    free(hashed_password);
}

int main() {
    OpenSSL_add_all_algorithms();
    register_user();
    EVP_cleanup();
    return 0;
}