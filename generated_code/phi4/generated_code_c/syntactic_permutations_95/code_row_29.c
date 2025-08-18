#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void hash_password(const char *password, unsigned char **hashed_password, size_t *hashed_length) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();

    if(!(mdctx = EVP_MD_CTX_new())) {
        fprintf(stderr, "Error creating MD context\n");
        exit(1);
    }

    if(1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        exit(1);
    }

    if(1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        fprintf(stderr, "Error updating digest\n");
        exit(1);
    }

    *hashed_length = EVP_MD_size(md);

    *hashed_password = malloc(*hashed_length);
    if(!(*hashed_password)) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    if(1 != EVP_DigestFinal_ex(mdctx, *hashed_password, hashed_length)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(1);
    }

    EVP_MD_CTX_free(mdctx);
}

int generate_salt(unsigned char *salt, size_t salt_size) {
    if(!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        return 0;
    }
    return 1;
}

void store_credentials(const char *username, const unsigned char *hashed_password, size_t hashed_length, const unsigned char *salt) {
    // Placeholder for database storage logic
    printf("Storing credentials:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: ");
    for(size_t i = 0; i < hashed_length + SALT_SIZE; ++i) {
        printf("%02x", i < hashed_length ? hashed_password[i] : salt[i - hashed_length]);
    }
    printf("\n");
}

int main() {
    char username[50];
    char password[100];

    unsigned char *hashed_password = NULL;
    size_t hashed_length = 0;

    unsigned char salt[SALT_SIZE];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if(!generate_salt(salt, SALT_SIZE)) {
        exit(1);
    }

    hash_password(password, &hashed_password, &hashed_length);

    unsigned char *stored_hashed_password = malloc(hashed_length + SALT_SIZE);
    memcpy(stored_hashed_password, hashed_password, hashed_length);
    memcpy(stored_hashed_password + hashed_length, salt, SALT_SIZE);

    store_credentials(username, stored_hashed_password, hashed_length + SALT_SIZE, NULL);

    free(hashed_password);
    free(stored_hashed_password);

    return 0;
}