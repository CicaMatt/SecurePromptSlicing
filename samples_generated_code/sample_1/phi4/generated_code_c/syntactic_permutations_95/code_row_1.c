#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASHED_PASSWORD_SIZE 32

void generate_salt(unsigned char *salt, size_t size) {
    if (RAND_bytes(salt, size) != 1) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        perror("EVP_MD_CTX_new failed");
        return 0;
    }

    if (1 != EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) {
        perror("EVP_DigestInit_ex failed");
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(ctx, password, strlen((char *)password))) {
        perror("EVP_DigestUpdate failed");
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(ctx, salt, SALT_SIZE)) {
        perror("EVP_DigestUpdate failed");
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    unsigned int len = 0;
    if (1 != EVP_DigestFinal_ex(ctx, output, &len)) {
        perror("EVP_DigestFinal_ex failed");
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    EVP_MD_CTX_free(ctx);

    if (len != sizeof(output)) {
        fprintf(stderr, "Hash length mismatch\n");
        return 0;
    }

    return 1;
}

void store_credentials(const char *username, const unsigned char *hashed_password) {
    // This function should implement the actual database storage logic.
    // Here we just print to standard output for demonstration purposes.

    printf("Storing credentials in database...\n");
    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): ");
    for (int i = 0; i < sizeof(hashed_password); ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Example of database storage logic:
    /*
    FILE *db_file = fopen("credentials.db", "a");
    if (!db_file) {
        perror("Failed to open database file");
        return;
    }

    fprintf(db_file, "%s %.*s\n", username, HASHED_PASSWORD_SIZE * 2, hashed_password);
    fclose(db_file);
    */
}

int main() {
    char username[100];
    unsigned char password[256];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%255s", (char *)password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password[HASHED_PASSWORD_SIZE];
    if (!hash_password(password, salt, hashed_password)) {
        fprintf(stderr, "Failed to hash password\n");
        return EXIT_FAILURE;
    }

    store_credentials(username, hashed_password);

    return 0;
}
