#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define PASSWORD_LEN 32

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) {
        exit(EXIT_FAILURE);
    }
    if (!EVP_DigestUpdate(ctx, password, strlen(password))) {
        exit(EXIT FAILURE);
    }
    unsigned int len;
    if (!EVP_DigestFinal_ex(ctx, output, &len)) {
        exit(EXIT_FAILURE);
    }
    EVP_MD_CTX_free(ctx);
}

int main() {
    char username[100];
    char password[PASSWORD_LEN];
    
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;
    
    unsigned char hashed_password[PASSWORD_LEN];
    hash_password(password, hashed_password);

    printf("\nRegistration successful!\n");
    printf("Username: %s\n", username);
    printf("Hashed Password (hex): ");
    for(int i = 0; i < EVP_MAX_MD_SIZE; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}