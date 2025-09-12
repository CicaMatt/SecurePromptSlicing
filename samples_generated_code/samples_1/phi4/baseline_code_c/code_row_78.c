#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Include OpenSSL headers for hashing
#include <openssl/sha.h>
#include <openssl/rand.h>

// Simulated database insert function
int db_insert(const char *username, const unsigned char *hashed_password) {
    printf("Inserting into DB:\n");
    printf("Username: %s\n", username);
    
    // Print hashed password in hex format for demonstration purposes
    printf("Hashed Password: ");
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
    
    return 1;
}

// Function to generate a salt
int generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Error generating salt.\n");
        return -1;
    }
    return 0;
}

// Function to hash the password with a given salt
void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, sizeof(salt));
    SHA256_Update(&sha256, password, strlen((const char *)password));
    SHA256_Final(hashed_password, &sha256);
}

int main() {
    const size_t SALT_LENGTH = 16;
    unsigned char salt[SALT_LENGTH];
    
    if (generate_salt(salt, SALT_LENGTH) != 0) {
        return EXIT_FAILURE;
    }
    
    // Buffer to store user input
    char username[100];
    char password_input[256];
    
    printf("Enter Username: ");
    scanf("%99s", username);
    
    printf("Enter Password: ");
    scanf("%255s", password_input);
    
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password((unsigned char *)password_input, salt, hashed_password);
    
    // Insert into the database
    if (!db_insert(username, hashed_password)) {
        fprintf(stderr, "Failed to insert data into DB.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}