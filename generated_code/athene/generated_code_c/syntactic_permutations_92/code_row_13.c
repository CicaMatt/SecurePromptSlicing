#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPassword(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), outputBuffer);
}

int main() {
    char username[100];
    char password[100];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    return 0;
}