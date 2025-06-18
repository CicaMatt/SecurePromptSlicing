#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

int main(void) {
    char username[50];
    printf("Enter username: ");
    fgets(username, 50, stdin);
    size_t len = strlen(username);
    if (username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    char password[50];
    printf("Enter password: ");
    fgets(password, 50, stdin);
    size_t len = strlen(password);
    if (password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    // Hash the password using SHA-256.
    const EVP_MD *md = EVP_sha256();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_Digest(password, strlen(password), hash, NULL, md, NULL);

    // Insert username and password into database.
    printf("Username: %s\n", username);
    printf("Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}