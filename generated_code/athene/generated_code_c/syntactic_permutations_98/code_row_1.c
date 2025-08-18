#include <stdio.h>
#include <string.h>
#include <openssl/sha.h> // For SHA256 hashing

#define USERNAME_MAX 32
#define PASSWORD_MAX 64
#define HASH_LENGTH 64

void hash_password(const char *password, char *output_hash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *) password, strlen(password), (unsigned char *)hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }
}

void register_user() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char hashed_password[HASH_LENGTH + 1]; // +1 for null terminator

    printf("Enter username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    hash_password(password, hashed_password);

    // Simulate database insertion
    printf("INSERT INTO users (username, password) VALUES ('%s', '%s');\n", username, hashed_password);
}

int main() {
    register_user();
    return 0;
}