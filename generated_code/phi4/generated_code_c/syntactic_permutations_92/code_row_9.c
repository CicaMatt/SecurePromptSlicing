#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define PASSWORD_LENGTH 64

void hashPassword(const char *password, unsigned char hashedPassword[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashedPassword, &sha256);
}

int main() {
    char username[50];
    char password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%63s", password);

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password (hex): ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    return 0;
}


To compile and run this code, you need to link against OpenSSL. Here is an example of how you might do that with `gcc`:


gcc -o registration_form registration_form.c -lssl -lcrypto
./registration_form