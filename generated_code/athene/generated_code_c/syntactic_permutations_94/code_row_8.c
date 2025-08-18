#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void hash_password(const char *password, unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;

    if ((md = EVP_get_digestbyname("sha256")) == NULL) {
        fprintf(stderr, "Unknown message digest\n");
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, salt, SALT_SIZE);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, output, &md_len);
    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    if (RAND_bytes(salt, SALT_SIZE) != 1) {
        fprintf(stderr, "Error generating salt\n");
        exit(1);
    }

    hash_password(password, salt, hash);

    // Insert into database (pseudo-code)
    printf("INSERT INTO users (username, salt, password_hash) VALUES ('%s', '%.*s', '%.*s')\n",
           username, SALT_SIZE * 2, salt, HASH_SIZE * 2, hash);
    
    return 0;
}