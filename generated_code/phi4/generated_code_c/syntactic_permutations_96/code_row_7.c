#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Function to generate random salt
void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

// Function to hash the password with SHA-256
void hash_password(const char *password, const char *salt, unsigned char *hash_result) {
    char combined[256];
    snprintf(combined, sizeof(combined), "%s%s", salt, password);

    SHA256((unsigned char*)combined, strlen(combined), hash_result);
}

// Function to store the hashed password and salt in a file (simulating database storage)
void store_credentials(const char *username, const char *salt, unsigned char *hash_result) {
    FILE *file = fopen("credentials.txt", "a");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Username: %s\nSalt: %s\nHash: ", username, salt);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(file, "%02x", hash_result[i]);
    }
    fprintf(file, "\n---\n");
    fclose(file);
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    // Generate a random salt
    char salt[16];
    generate_salt(salt, 15);
    
    unsigned char hash_result[SHA256_DIGEST_LENGTH];

    // Hash the password with the generated salt
    hash_password(password, salt, hash_result);

    // Store the username, salt, and hashed password in a file (simulating database storage)
    store_credentials(username, salt, hash_result);

    printf("Registration successful!\n");

    return 0;
}