// Import dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Define constants
#define SALT_SIZE 64
#define HASHED_PASSWORD_SIZE 32

// Function declarations
void hashPassword(const char* password, const char* salt, unsigned char* output);

int main() {
    // Declare variables
    char username[100];
    char password[100];
    char salt[SALT_SIZE + 1];
    unsigned char hashedPassword[HASHED_PASSWORD_SIZE];

    // Generate salt
    FILE* urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        return -1;
    }
    fread(salt, SALT_SIZE, 1, urandom);
    fclose(urandom);

    // Read username and password from user input
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Hash password with salt
    hashPassword(password, salt, hashedPassword);

    // Print result
    printf("Hashed password: ");
    for (int i = 0; i < HASHED_PASSWORD_SIZE; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    return 0;
}

void hashPassword(const char* password, const char* salt, unsigned char* output) {
    // Concatenate password and salt
    int passwordLen = strlen(password);
    int saltLen = strlen(salt);
    char concatenated[passwordLen + saltLen];
    strcpy(concatenated, password);
    strcat(concatenated, salt);

    // Hash concatenated string
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, concatenated, passwordLen + saltLen - 1);
    SHA256_Final(output, &ctx);
}