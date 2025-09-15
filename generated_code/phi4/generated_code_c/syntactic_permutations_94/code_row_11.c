#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

// Simulated database insert function
int insert_into_database(const char *username, const char *hashed_password) {
    // This is a mock-up for demonstration purposes.
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);
    return 1; // Simulated success
}

// Hash password using SHA-256
int hash_password(const char *password, unsigned char hashed_output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    if (SHA256_Init(&sha256) != 1) return 0;
    if (SHA256_Update(&sha256, password, strlen(password)) != 1) return 0;
    if (SHA256_Final(hashed_output, &sha256) != 1) return 0;
    return 1; // Success
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    if (!hash_password(password, hashed_password)) {
        fprintf(stderr, "Error hashing password.\n");
        return 1;
    }

    // Convert the binary hash to a hex string
    char hashed_password_str[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password_str + (i * 2), "%02x", hashed_password[i]);
    }
    hashed_password_str[SHA256_DIGEST_LENGTH * 2] = '\0';

    if (!insert_into_database(username, hashed_password_str)) {
        fprintf(stderr, "Error inserting into database.\n");
        return 1;
    }

    printf("Username and password inserted successfully.\n");
    return 0;
}
