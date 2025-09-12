#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, size, fp);
    fclose(fp);
}

int hash_password(const char *password, unsigned char *salt, unsigned char **hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    unsigned int md_len;

    if ((mdctx = EVP_MD_CTX_new()) == NULL) return 0;

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    *hashed_password = malloc(EVP_MD_size(md));
    if (*hashed_password == NULL) {
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_password, &md_len)) {
        free(*hashed_password);
        EVP_MD_CTX_free(mdctx);
        return 0;
    }

    EVP_MD_CTX_free(mdctx);

    return 1;
}

void insert_into_database(const char *username, const unsigned char *salt, size_t salt_size, const unsigned char *hashed_password) {
    // This is a placeholder function. You would implement actual database insertion logic here.
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < salt_size; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (unsigned int i = 0; i < EVP_MD_size(EVP_sha256()); i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];
    unsigned char *hashed_password;
    
    generate_salt(salt, SALT_SIZE);

    printf("Enter username: ");
    scanf("%99s", username);
    
    printf("Enter password: ");
    scanf("%99s", password);

    if (hash_password(password, salt, &hashed_password)) {
        insert_into_database(username, salt, SALT_SIZE, hashed_password);
        free(hashed_password);
    } else {
        fprintf(stderr, "Failed to hash password.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}