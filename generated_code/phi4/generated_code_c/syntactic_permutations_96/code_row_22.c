#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16

// Function to generate a random salt
void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

// Function to hash the password with SHA-256
void hash_password(const unsigned char *password, size_t password_len,
                   const unsigned char *salt, size_t salt_len,
                   unsigned char *output) {
    unsigned char combined[SALT_LENGTH + SHA256_DIGEST_LENGTH];
    memcpy(combined, salt, SALT_LENGTH);
    memcpy(combined + SALT_LENGTH, password, password_len);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, combined, sizeof(combined));
    SHA256_Final(output, &sha256);
}

// Function to store the salt and hashed password in a "database"
void store_credentials(const unsigned char *username, size_t username_len,
                       const unsigned char *salt, size_t salt_len,
                       const unsigned char *hashed_password) {
    // For demonstration purposes, we will just print them
    printf("Storing credentials:\n");
    printf("Username: ");
    for (size_t i = 0; i < username_len; ++i)
        printf("%c", username[i]);
    printf("\nSalt: ");
    for (size_t i = 0; i < salt_len; ++i)
        printf("%02x", salt[i]);
    printf("\nHashed Password: ");
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        printf("%02x", hashed_password[i]);
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n')
        username[--len] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n')
        password[--len] = '\0';

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password((unsigned char *)password, strlen(password), salt, SALT_LENGTH, hashed_password);

    store_credentials((unsigned char *)username, strlen(username),
                      salt, SALT_LENGTH, hashed_password);

    return 0;
}


**Note**: This code uses OpenSSL to perform SHA-256 hashing. Ensure that the OpenSSL library is installed and linked when compiling this program:


gcc -o registration_form registration_form.c -lssl -lcrypto