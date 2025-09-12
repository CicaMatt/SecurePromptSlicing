#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp != NULL) {
        fread(salt, 1, size, fp);
        fclose(fp);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        exit(1);
    }

    if (!EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        exit(1);
    }
    
    if (!EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        exit(1);
    }
    
    unsigned int len = 0;
    if (!EVP_DigestFinal_ex(mdctx, hash, &len)) {
        exit(1);
    }

    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[256];
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];
    printf("Enter password: ");
    char *password = NULL;
    size_t len = 0;
    getline(&password, &len, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password((const unsigned char *)password, salt, hash);

    printf("Username: %s\n", username);
    printf("Hashed Password (hex): ");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    free(password);
    return 0;
}