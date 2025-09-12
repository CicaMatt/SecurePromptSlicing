#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate hashing a password
void hash_password(const char *password, char *hashed) {
    // Simple hashing simulation: reverse string (for demonstration purposes only)
    size_t len = strlen(password);
    for (size_t i = 0; i < len; ++i) {
        hashed[i] = password[len - 1 - i];
    }
    hashed[len] = '\0';
}

// Mock function to simulate inserting into a database
int insert_into_database(const char *username, const char *hashed_password) {
    // In a real-world scenario, this would involve SQL operations with a library like MySQL or SQLite.
    printf("Inserting user: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);
    return 0; // Return success
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from username input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from password input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    char hashed_password[100];
    hash_password(password, hashed_password);

    insert_into_database(username, hashed_password);

    return 0;
}