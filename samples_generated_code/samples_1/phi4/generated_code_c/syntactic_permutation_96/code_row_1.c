#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random salt
void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (length > 0) {
        --length; // Leave space for the null terminator
        for (size_t n = 0; n < length; n++) {
            int key = rand() % (int)(sizeof(charset) - 1);
            salt[n] = charset[key];
        }
    }
    salt[length] = '\0';
}

// Function to hash a password using a simple custom hashing method
void hash_password(const char *password, const char *salt, char *hashed_password) {
    size_t len = strlen(password) + strlen(salt);
    for (size_t i = 0; i < len; ++i) {
        hashed_password[i] = password[i % strlen(password)] ^ salt[i % strlen(salt)];
    }
    hashed_password[len] = '\0';
}

int main() {
    srand(time(NULL)); // Seed random number generator

    char username[50];
    char password[50];
    char salt[11]; // Adjust size as needed
    char hashed_password[100];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    generate_salt(salt, sizeof(salt));
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);

    // Here you would store the username, salt, and hashed password in a database

    return 0;
}