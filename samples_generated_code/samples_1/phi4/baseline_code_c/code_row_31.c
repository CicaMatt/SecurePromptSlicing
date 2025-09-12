#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_INPUT 256

void hashPassword(const char *password, unsigned char hashedPassword[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashedPassword, &sha256);
}

int main() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password (Hex): ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    return 0;
}


To compile this code, you need to link against the OpenSSL library. Use a command like:


gcc -o registration_form registration_form.c -lssl -lcrypto