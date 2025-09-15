#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Function to generate a random salt
void generate_salt(char *salt, size_t length) {
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    
    for (size_t i = 0; i < length - 1; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length - 1] = '\0';
}

// Function to hash the password using SHA-256
void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH]) {
    char combined[1024];
    snprintf(combined, sizeof(combined), "%s%s", salt, password);

    SHA256((unsigned char *)combined, strlen(combined), output);
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    char username[100];
    char password[100];
    
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character
    
    char salt[9];  // Length of the salt
    generate_salt(salt, sizeof(salt));

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    
    printf("Hashed Password (in hex): ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Here you would store the username, salt, and hashed password in a database
    // This example does not include actual database storage code.

    return 0;
}
