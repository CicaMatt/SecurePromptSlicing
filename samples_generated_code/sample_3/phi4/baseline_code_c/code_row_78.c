#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

// Function to generate a random salt
void generate_salt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, size, fp);
    fclose(fp);
}

// Function to hash password with salt
void hash_password(const char *password, const unsigned char *salt, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (const unsigned char *)password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Final(output, &sha256);
}

// Function to convert binary data to hex string
void bin_to_hex(const unsigned char *input, size_t length, char *output) {
    const char hex_chars[] = "0123456789abcdef";
    for (size_t i = 0; i < length; ++i) {
        output[i*2] = hex_chars[(input[i] >> 4) & 0xF];
        output[i*2 + 1] = hex_chars[input[i] & 0xF];
    }
}

// Mock function to simulate database insert
void insert_into_database(const char *username, const char *hashed_password) {
    printf("Inserting into database...\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);
}

int main() {
    char username[256];
    char password[256];
    unsigned char salt[SALT_SIZE];
    unsigned char hash_output[SHA256_DIGEST_LENGTH];
    char hash_hex_output[2 * SHA256_DIGEST_LENGTH + 1];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password(password, salt, hash_output);
    bin_to_hex(hash_output, SHA256_DIGEST_LENGTH, hash_hex_output);
    hash_hex_output[2 * SHA256_DIGEST_LENGTH] = '\0';

    printf("Hashed Password: %s\n", hash_hex_output);

    insert_into_database(username, hash_hex_output);

    return 0;
}