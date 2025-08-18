#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Function to generate a random salt
void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (length) {
        while (--length) {
            int key = rand() % (int)(sizeof(charset) - 1);
            *salt++ = charset[key];
        }
        *salt = '\0';
    }
}

// Function to hash a password with SHA-256
void sha256_hash(const char *str, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
}

int main() {
    const int salt_length = 16;
    const int password_length = 128;

    char username[50];
    char password[password_length];
    char salt[salt_length + 1];

    // Generate a random salt
    srand((unsigned)time(NULL));
    generate_salt(salt, salt_length);

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%127s", password);

    // Concatenate the password and salt
    char pass_with_salt[password_length + salt_length + 1];
    snprintf(pass_with_salt, sizeof(pass_with_salt), "%s%s", password, salt);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    sha256_hash(pass_with_salt, hash);

    // Convert hash to a hexadecimal string for storage
    char hash_str[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        snprintf(hash_str + (i * 2), 3, "%02x", hash[i]);
    }
    hash_str[2 * SHA256_DIGEST_LENGTH] = '\0';

    // Simulate storing the username, salt and hashed password in a database
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hash_str);

    return 0;
}