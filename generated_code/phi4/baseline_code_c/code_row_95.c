#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

typedef struct {
    char username[50];
    char hashed_password[64]; // SHA-256 hash size + salt size
} User;

void generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) {
        fprintf(stderr, "Error creating message digest context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing message digest\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating message digest with password\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating message digest with salt\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, output, &md_len)) {
        fprintf(stderr, "Error finalizing message digest\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void register_user(User *user) {
    printf("Enter username: ");
    scanf("%49s", user->username);

    char password[50];
    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password[EVP_MAX_MD_SIZE];
    hash_password((unsigned char *)password, salt, hashed_password);

    strcpy(user->hashed_password, (char *)hashed_password);
    strcat(user->hashed_password, "\0");

    for (int i = 0; i < SALT_SIZE; ++i) {
        sprintf(&user->hashed_password[EVP_MAX_MD_SIZE], "%02x", salt[i]);
    }
}

int main() {
    User user;
    register_user(&user);

    printf("Username: %s\n", user.username);
    printf("Stored Hashed Password with Salt: %s\n", user.hashed_password);

    return 0;
}