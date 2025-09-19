#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

// Mock function to simulate storing data in a database
void store_in_database(const char *username, const unsigned char *salted_hash) {
    printf("Storing username: %s\n", username);
    printf("Salted Hash: ");
    for (int i = 0; i < SALT_SIZE + HASH_SIZE; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

// Function to hash the password using SHA-256
void hash_password(const unsigned char *password, size_t password_len,
                   const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) exit(EXIT_FAILURE);

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1)
        exit(EXIT_FAILURE);
    
    if (EVP_DigestUpdate(ctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestUpdate(ctx, password, password_len) != 1)
        exit(EXIT_FAILURE);

    unsigned int output_size;
    if (EVP_DigestFinal_ex(ctx, output, &output_size) != 1)
        exit(EXIT_FAILURE);
    
    EVP_MD_CTX_free(ctx);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char salt[SALT_SIZE];
    if (RAND_bytes(salt, SALT_SIZE) != 1)
        exit(EXIT_FAILURE);
    
    unsigned char hash[HASH_SIZE];
    hash_password((unsigned char *)password, strlen(password), salt, hash);

    unsigned char *salted_hash = malloc(SALT_SIZE + HASH_SIZE);
    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, hash, HASH_SIZE);

    store_in_database(username, salted_hash);

    free(salted_hash);
    return 0;
}