#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hashPassword(const char* password, unsigned char* digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hashPassword(password, hash);

    char* hashedPassword = (char*)malloc(SHA256_DIGEST_LENGTH * sizeof(char) + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashedPassword[i * 2], "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';

    // Simulate database insertion
    printf("Registering user '%s' with hashed password '%s'\n", username, hashedPassword);

    free(hashedPassword);
    return 0;
}