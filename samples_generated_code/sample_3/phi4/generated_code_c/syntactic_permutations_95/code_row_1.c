#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Error creating context\n");
        exit(EXIT_FAILURE);
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1 ||
        EVP_DigestUpdate(ctx, password, strlen((const char *)password)) != 1 ||
        EVP_DigestUpdate(ctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestFinal_ex(ctx, hash, NULL) != 1) {
        fprintf(stderr, "Error hashing password\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(ctx);
}

void store_credentials(const char *username, const unsigned char *hashed_password) {
    // Simulating database storage with a file
    FILE *file = fopen("credentials.db", "a");
    if (!file) {
        fprintf(stderr, "Error opening credentials file\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s:%.*s\n", username, HASH_SIZE + SALT_SIZE, hashed_password);

    fclose(file);
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];
    hash_password((unsigned char *)password, salt, hash);

    unsigned char hashed_password[HASH_SIZE + SALT_SIZE];
    memcpy(hashed_password, hash, HASH_SIZE);
    memcpy(hashed_password + HASH_SIZE, salt, SALT_SIZE);

    store_credentials(username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}


To compile and run the code, you will need OpenSSL development libraries installed. Use the following command to compile:


gcc -o registration_form registration_form.c -lcrypto


Then execute it with:


./registration_form