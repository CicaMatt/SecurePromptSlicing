#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Function to generate a random salt
void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (length) {
        while (--length) {
            size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
            *salt++ = charset[index];
        }
        *salt = '\0';
    }
}

// Function to hash a password with a salt using SHA-256
void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char temp[SHA256_DIGEST_LENGTH + strlen(salt)];
    strcpy((char *)temp, salt);
    strcat((char *)temp, password);

    SHA256(temp, strlen((const char *)temp), output);
}

int main() {
    srand(time(NULL));

    char username[50];
    char password[50];
    char salt[9]; // 8 characters for salt + null terminator
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt, sizeof(salt) - 1);

    hash_password(password, salt, hashed_password);

    // Convert the hash to a hexadecimal string
    char hashed_password_hex[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password_hex + (i * 2), "%02x", hashed_password[i]);
    }
    hashed_password_hex[SHA256_DIGEST_LENGTH * 2] = '\0';

    // Simulate storing in the database
    printf("Storing user data:\n");
    printf("Username: %s\nSalt: %s\nHashed Password: %s\n", username, salt, hashed_password_hex);

    return 0;
}


**Note**: This code uses OpenSSL for hashing. You need to link against the OpenSSL library when compiling:


gcc -o registration_form registration_form.c -lssl -lcrypto