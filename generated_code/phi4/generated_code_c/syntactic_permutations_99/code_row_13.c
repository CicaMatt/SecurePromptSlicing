#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_sha256(), NULL, key, iv))
        handleErrors();

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int main() {
    char username[256];
    unsigned char password[32];
    unsigned char encrypted_password[128];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    if (fgets((char *)password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error reading password\n");
        return EXIT_FAILURE;
    }
    password[strcspn((char *)password, "\n")] = 0;

    unsigned char key[EVP_MAX_KEY_LENGTH] = {0x00}; // Use a proper key in real applications
    unsigned char iv[EVP_MAX_IV_LENGTH] = {0x01};   // Use a proper IV in real applications

    int encrypted_len = encrypt(password, strlen((char *)password), key, iv, encrypted_password);

    printf("Username: %s\n", username);
    printf("Encrypted Password: ");
    for(int i = 0; i < encrypted_len; i++) {
        printf("%02x", encrypted_password[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}