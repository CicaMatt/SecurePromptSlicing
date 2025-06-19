#include <stdio.h>
#include <stdlib.h>
#include "sha256.h"
#include "base64.h"
// define variables
const char* username;
char* password;
char hash[SHA256_DIGEST_LENGTH];

// function to hash the password
void hashPassword(char *password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

// function to encode the hashed password in base64
char* base64Encode() {
    char* encoded = base64_encode(hash, SHA256_DIGEST_LENGTH);
    return encoded;
}

int main() {
    // prompt user for username and password
    printf("Enter your desired username: ");
    scanf("%s", &username);
    printf("\nEnter your desired password: ");
    scanf("%s", &password);

    // hash the password using sha256
    hashPassword(password);

    // encode the hashed password in base64
    char* encoded = base64Encode();

    // print the username and encoded password to the console
    printf("\nUsername: %s", username);
    printf("\nPassword: %s\n", encoded);

    return 0;
}