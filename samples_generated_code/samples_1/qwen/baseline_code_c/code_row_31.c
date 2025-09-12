#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPassword(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void printHash(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
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
    printHash(hashedPassword);

    return 0;
}