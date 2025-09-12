#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT_SIZE 256

void hash_password(const char *password, unsigned char **digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();
    if (!EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        return;
    }
    
    if (!EVP_DigestUpdate(mdctx, password, strlen(password))) {
        fprintf(stderr, "Error updating digest\n");
        return;
    }

    unsigned int len = 0;
    if (!EVP_DigestFinal_ex(mdctx, *digest, &len)) {
        fprintf(stderr, "Error finalizing digest\n");
        return;
    }

    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];

    printf("Enter username: ");
    fgets(username, MAX_INPUT_SIZE, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_INPUT_SIZE, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char *digest;
    digest = malloc(EVP_MAX_MD_SIZE);

    hash_password(password, &digest);

    printf("Username: %s\n", username);
    printf("Password Hash (SHA-256): ");
    for(int i = 0; i < EVP_MD_size(EVP_sha256()); i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    free(digest);
    
    return 0;
}