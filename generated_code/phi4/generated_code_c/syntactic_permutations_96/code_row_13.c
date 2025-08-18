#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

// Function to generate a random salt
int generate_salt(unsigned char *salt, size_t salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating salt\n");
        return -1;
    }
    return 0;
}

// Function to hash the password with the given salt using SHA-256
void hash_password(const unsigned char *password, const unsigned char *salt, size_t salt_size, unsigned char **hashed) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }
    
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        EVP_MD_CTX_free(mdctx);
        fprintf(stderr, "Error initializing digest\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, salt_size)) {
        EVP_MD_CTX_free(mdctx);
        fprintf(stderr, "Error updating digest with salt\n");
        exit(EXIT_FAILURE);
    }
    
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        EVP_MD_CTX_free(mdctx);
        fprintf(stderr, "Error updating digest with password\n");
        exit(EXIT_FAILURE);
    }

    *hashed = malloc(EVP_MAX_MD_SIZE);
    unsigned int length_of_hashed;
    
    if (1 != EVP_DigestFinal_ex(mdctx, *hashed, &length_of_hashed)) {
        free(*hashed);
        EVP_MD_CTX_free(mdctx);
        fprintf(stderr, "Error finalizing digest\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

// Function to store the salt and hashed password in a simple text database
void store_credentials(const char *username, const unsigned char *salt, size_t salt_size, const unsigned char *hashed, unsigned int hashed_len) {
    FILE *db = fopen("database.txt", "a");
    if (!db) {
        fprintf(stderr, "Error opening database file\n");
        exit(EXIT_FAILURE);
    }

    fprintf(db, "%s,%.*H\n", username, (int)salt_size, salt);
    fprintf(db, "%.*H\n", (int)hashed_len, hashed);

    fclose(db);
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    if (generate_salt(salt, SALT_SIZE) != 0) {
        exit(EXIT_FAILURE);
    }

    unsigned char *hashed;
    hash_password((unsigned char *)password, salt, SALT_SIZE, &hashed);

    store_credentials(username, salt, SALT_SIZE, hashed, EVP_MAX_MD_SIZE);

    free(hashed);

    printf("Registration successful!\n");

    return 0;
}