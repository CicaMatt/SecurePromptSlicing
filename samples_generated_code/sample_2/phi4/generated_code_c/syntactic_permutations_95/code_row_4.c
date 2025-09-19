#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

// Function prototypes
void generateSalt(unsigned char *salt, size_t size);
void hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char *hashOutput);
int saveToDatabase(const char *username, const unsigned char *hashedPasswordWithSalt);

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char salt[SALT_SIZE];
    generateSalt(salt, SALT_SIZE);

    unsigned char hashOutput[SHA256_DIGEST_LENGTH + SALT_SIZE];
    hashPassword((unsigned char *)password, salt, hashOutput);

    if (saveToDatabase(username, hashOutput)) {
        printf("Registration successful.\n");
    } else {
        printf("Failed to save registration details.\n");
    }

    return 0;
}

void generateSalt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Unable to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, size, fp);
    fclose(fp);
}

void hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char *hashOutput) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen((const char *)password));
    SHA256_Final(hash, &sha256);

    memcpy(hashOutput, hash, SHA256_DIGEST_LENGTH);
    memcpy(hashOutput + SHA256_DIGEST_LENGTH, salt, SALT_SIZE);
}

int saveToDatabase(const char *username, const unsigned char *hashedPasswordWithSalt) {
    // Simulate saving to a database by printing to the console
    printf("Saving user: %s\n", username);

    printf("Hashed password with salt (in hex): ");
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH + SALT_SIZE; ++i) {
        printf("%02x", hashedPasswordWithSalt[i]);
    }
    printf("\n");

    // Return 1 to indicate success
    return 1;
}