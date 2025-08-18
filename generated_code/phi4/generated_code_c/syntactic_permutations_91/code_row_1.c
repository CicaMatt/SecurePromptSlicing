#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Define a structure for User
typedef struct {
    char username[50];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

// Function to hash the password using SHA-256
void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    User user;
    char password[100];

    printf("Enter username: ");
    fgets(user.username, sizeof(user.username), stdin);
    // Remove newline character from username
    size_t len = strlen(user.username);
    if (len > 0 && user.username[len - 1] == '\n') {
        user.username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from password
    if (strlen(password) > 0 && password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0';
    }

    hash_password(password, user.password_hash);

    // Simulate inserting into a database by printing to console
    printf("User registered successfully!\n");
    printf("Username: %s\n", user.username);
    printf("Password Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", user.password_hash[i]);
    }
    printf("\n");

    return 0;
}


To compile and run this code, you need to have OpenSSL library installed. You can compile it using:


gcc -o register_app register_app.c -lssl -lcrypto
./register_app