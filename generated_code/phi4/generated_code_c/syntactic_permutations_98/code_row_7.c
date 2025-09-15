#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_NAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_NAME_LEN];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    // Simulating a simple database
    User users[10];
    int user_count = 0;

    char username[MAX_NAME_LEN], password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    // Copy the username and hashed password to the user structure
    strncpy(users[user_count].username, username, MAX_NAME_LEN);
    memcpy(users[user_count].password_hash, hashed_password, SHA256_DIGEST_LENGTH);

    printf("User registered successfully!\n");

    return 0;
}
