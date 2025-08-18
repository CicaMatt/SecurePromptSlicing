#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_LENGTH 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    printf("Username: %s\n", username);
    printf("Password Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}


To compile this code, ensure you have OpenSSL installed and use:

gcc -o registration_form registration_form.c -lcrypto
./registration_form