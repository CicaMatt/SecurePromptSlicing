#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

typedef struct {
    char username[50];
    unsigned char salt[SALT_SIZE];
    unsigned char hashed_password[EVP_MAX_MD_SIZE];
} User;

void generate_salt(unsigned char *salt, size_t size) {
    if (!RAND_bytes(salt, size)) {
        fprintf(stderr, "Error generating random bytes.\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const char *password, unsigned char salt[], unsigned char hashed_password[]) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) return 0;

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1 ||
        EVP_DigestUpdate(ctx, password, strlen(password)) != 1 ||
        EVP_DigestUpdate(ctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestFinal_ex(ctx, hashed_password, NULL) != 1) {
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    EVP_MD_CTX_free(ctx);
    return 1;
}

void register_user(const char *username, const char *password) {
    User user;
    strcpy(user.username, username);

    generate_salt(user.salt, SALT_SIZE);

    if (!hash_password(password, user.salt, user.hashed_password)) {
        fprintf(stderr, "Error hashing password.\n");
        exit(EXIT_FAILURE);
    }

    // Simulate storing in a database
    printf("Storing User: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", user.salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < EVP_MD_size(EVP_sha256()); ++i) {
        printf("%02x", user.hashed_password[i]);
    }
    printf("\n");
}

void verify_password(const char *username, const char *password, const unsigned char salt[], const unsigned char hashed_password[]) {
    unsigned char new_hashed_password[EVP_MAX_MD_SIZE];

    if (!hash_password(password, (unsigned char *)salt, new_hashed_password)) {
        fprintf(stderr, "Error hashing password.\n");
        exit(EXIT_FAILURE);
    }

    if (memcmp(hashed_password, new_hashed_password, EVP_MD_size(EVP_sha256())) == 0) {
        printf("Password verified for user: %s\n", username);
    } else {
        printf("Password verification failed for user: %s\n", username);
    }
}

int main() {
    const char *username = "testuser";
    const char *password = "securepassword123";

    register_user(username, password);

    // Simulate login
    unsigned char stored_salt[SALT_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
                                            0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    unsigned char stored_hashed_password[EVP_MAX_MD_SIZE] = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
                                                             0x07, 0x18, 0x29, 0x3A, 0x4B, 0x5C,
                                                             0x6D, 0x7E, 0x8F, 0x90};

    verify_password(username, password, stored_salt, stored_hashed_password);

    return 0;
}
