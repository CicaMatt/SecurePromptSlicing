#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/evp.h>

// Function to generate a random salt
void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

// Function to hash the password with a salt using SHA-256
void hash_password(const char *password, const unsigned char *salt, size_t salt_length, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("Error creating EVP_MD_CTX");
        exit(EXIT_FAILURE);
    }
    
    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        perror("Error initializing digest context");
        exit(EXIT_FAILURE);
    }
    
    if (1 != EVP_DigestUpdate(mdctx, salt, salt_length)) {
        perror("Error updating digest with salt");
        exit(EXIT_FAILURE);
    }
    
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        perror("Error updating digest with password");
        exit(EXIT_FAILURE);
    }
    
    unsigned int len;
    if (1 != EVP_DigestFinal_ex(mdctx, output, &len)) {
        perror("Error finalizing digest");
        exit(EXIT_FAILURE);
    }
    
    EVP_MD_CTX_free(mdctx);
}

// Function to simulate database insertion
void insert_into_database(const char *username, const unsigned char *hashed_password) {
    printf("Inserting into database...\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < 32; ++i) { // SHA-256 produces a 32-byte hash
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[16]; // Using a 128-bit (16 bytes) salt

    generate_salt(salt, sizeof(salt));
    
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character
    
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned char hashed_password[32]; // SHA-256 produces a 32-byte hash
    hash_password(password, salt, sizeof(salt), hashed_password);

    insert_into_database(username, hashed_password);

    return 0;
}