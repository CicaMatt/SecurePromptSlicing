#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define SALT_SIZE 16

// Simple hash function for demonstration purposes (not secure)
void simple_hash(const char *input, size_t input_len, uint8_t *output) {
    for (size_t i = 0; i < input_len && i < sizeof(output); ++i) {
        output[i] = (uint8_t)input[i];
    }
}

// Generate a random salt
void generate_salt(uint8_t *salt, size_t len) {
    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < len; ++i) {
        salt[i] = rand() % 256;
    }
}

// Hash the password with the salt and store it
void register_user(const char *username, const char *password) {
    uint8_t salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    // Hash the password with the salt
    uint8_t hash[16]; // Assuming 16-byte hash for simplicity
    simple_hash(password, strlen(password), hash);
    
    // Append salt to the hash (for demonstration purposes)
    uint8_t hashed_password_with_salt[sizeof(hash) + SALT_SIZE];
    memcpy(hashed_password_with_salt, hash, sizeof(hash));
    memcpy(hashed_password_with_salt + sizeof(hash), salt, SALT_SIZE);

    // Store username and hashed password with salt in a "database"
    // For demonstration purposes, we'll just print it
    printf("Registering user: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (size_t i = 0; i < sizeof(hashed_password_with_salt); ++i) {
        printf("%02x", hashed_password_with_salt[i]);
    }
    printf("\n");
}

// Verify the password during login
int verify_user(const char *username, const char *password, uint8_t *stored_hashed_password_with_salt) {
    uint8_t hash[16];
    simple_hash(password, strlen(password), hash);

    // Extract salt from stored hashed password with salt
    uint8_t extracted_salt[SALT_SIZE];
    memcpy(extracted_salt, stored_hashed_password_with_salt + sizeof(hash), SALT_SIZE);

    // Re-hash the input password with extracted salt
    uint8_t rehashed_password_with_salt[sizeof(hash) + SALT_SIZE];
    memcpy(rehashed_password_with_salt, hash, sizeof(hash));
    memcpy(rehashed_password_with_salt + sizeof(hash), extracted_salt, SALT_SIZE);

    // Compare stored hashed password with re-hashed password
    return memcmp(stored_hashed_password_with_salt, rehashed_password_with_salt, sizeof(hashed_password_with_salt)) == 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    // Register the user
    register_user(username, password);

    // Simulate login attempt
    uint8_t stored_hashed_password_with_salt[sizeof(uint8_t) * 16 + SALT_SIZE]; // Placeholder for demonstration

    printf("Enter username to login: ");
    scanf("%49s", username);

    printf("Enter password to login: ");
    scanf("%49s", password);

    if (verify_user(username, password, stored_hashed_password_with_salt)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials.\n");
    }

    return 0;
}