#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void handleErrors(void) {
    fprintf(stderr, "Error occurred\n");
    exit(EXIT_FAILURE);
}

unsigned char *generate_salt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        handleErrors();
    }
    return salt;
}

unsigned char *hash_password(const unsigned char *password, const unsigned char *salt, int password_len, int salt_len) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (ctx == NULL) handleErrors();

    const EVP_MD *md = EVP_sha256();
    if (!EVP_DigestInit_ex(ctx, md, NULL)) handleErrors();

    if (!EVP_DigestUpdate(ctx, password, password_len)) handleErrors();
    if (!EVP_DigestUpdate(ctx, salt, salt_len)) handleErrors();

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    if (!EVP_DigestFinal_ex(ctx, hash, &hash_len)) handleErrors();
    EVP_MD_CTX_free(ctx);

    unsigned char *result = malloc(hash_len);
    if (result == NULL) handleErrors();

    memcpy(result, hash, hash_len);
    return result;
}

void insert_into_database(const char *username, const unsigned char *hashed_password, size_t hashed_password_len) {
    // This function simulates database insertion.
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    
    printf("Hashed Password: ");
    for (size_t i = 0; i < hashed_password_len; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // In a real application, you would use an actual database API to store these values.
}

int main(void) {
    char username[100];
    char password[100];

    unsigned char salt[SALT_SIZE];
    
    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) return 1;
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) return 1;
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    generate_salt(salt, SALT_SIZE);

    unsigned char *hashed_password = hash_password((unsigned const char *)password, salt, strlen(password), SALT_SIZE);
    
    insert_into_database(username, hashed_password, EVP_MAX_MD_SIZE);

    free(hashed_password);

    return 0;
}


This code uses OpenSSL to handle the hashing and salting of passwords. Make sure you have OpenSSL installed and linked correctly for compiling this code (e.g., using `-lssl -lcrypto` with GCC).