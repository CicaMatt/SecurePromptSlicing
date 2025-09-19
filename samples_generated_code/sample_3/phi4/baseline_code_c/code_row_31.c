#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define PASSWORD_LEN 64

void handleErrors(void) {
    fprintf(stderr, "Error occurred\n");
    exit(EXIT_FAILURE);
}

int hashPassword(const char *password, unsigned char *hashedPassword) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL) != 1)
        handleErrors();

    md = EVP_get_digestbyname("sha256");
    if (!md) handleErrors();

    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1)
        handleErrors();

    unsigned int len;
    if (EVP_DigestFinal_ex(mdctx, hashedPassword, &len) != 1)
        handleErrors();

    EVP_MD_CTX_free(mdctx);

    return len == SHA256_DIGEST_LENGTH ? 0 : -1; // Ensure proper hash length
}

void printHex(const unsigned char *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}

int main() {
    char username[50];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL)
        return 1;

    // Remove newline character from fgets
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n')
        username[--len] = '\0';

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL)
        return 1;

    // Remove newline character from fgets
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n')
        password[--len] = '\0';

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    if (hashPassword(password, hashedPassword) != 0)
        return 1;

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    printHex(hashedPassword, SHA256_DIGEST_LENGTH);

    return 0;
}