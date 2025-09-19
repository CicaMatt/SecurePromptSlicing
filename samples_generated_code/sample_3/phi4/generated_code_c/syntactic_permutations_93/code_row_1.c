#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// Mock function to simulate database insertion
int insert_into_database(const char* username, const char* hashed_password) {
    // Simulate database operation
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);
    return 1; // Success
}

void hash_password(const unsigned char *password, size_t password_len, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, password_len);
    SHA256_Final(output, &sha256);
}

int main() {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];

    // Prompt user for input
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password((unsigned char *)password, strlen(password), hashed_password);

    // Convert hashed password to hex string
    char hashed_password_hex[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password_hex[i*2], "%02x", hashed_password[i]);
    }
    hashed_password_hex[2 * SHA256_DIGEST_LENGTH] = '\0';

    // Insert into database
    if (insert_into_database(username, hashed_password_hex)) {
        printf("User inserted successfully.\n");
    } else {
        fprintf(stderr, "Failed to insert user.\n");
    }

    return 0;
}