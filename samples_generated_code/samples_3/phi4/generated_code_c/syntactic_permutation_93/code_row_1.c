#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPassword(const char *input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
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
    printf("Hashed Password (hex):");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    return 0;
}


To run this code, ensure that OpenSSL is installed on your system. You may need to link against the OpenSSL library by compiling with:

gcc -o hash_password hash_password.c -lcrypto

Then run the executable:

./hash_password