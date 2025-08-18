#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_LENGTH 256

void hash_password(const char* input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}


Make sure to link with OpenSSL when compiling this code. For example, using GCC:


gcc -o registration_form registration_form.c -lcrypto