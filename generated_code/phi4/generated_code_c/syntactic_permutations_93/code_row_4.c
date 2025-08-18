#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    // Get username and password from user
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Hash the password using SHA-256
    hash_password(password, hashedPassword);

    // Convert the binary hash to a hexadecimal string
    char hashedPasswordHex[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashedPasswordHex[i * 2], "%02x", hashedPassword[i]);
    }
    hashedPasswordHex[2 * SHA256_DIGEST_LENGTH] = '\0';

    // Normally, you would insert these into a database here
    printf("Username: %s\n", username);
    printf("Hashed Password (hex): %s\n", hashedPasswordHex);

    // Simulate insertion into the database by just printing to console
    // In real application, use database API to insert data
    printf("Inserting into database...\n");

    return 0;
}