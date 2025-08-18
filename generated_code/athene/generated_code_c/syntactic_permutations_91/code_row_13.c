#include <stdio.h>
#include <string.h>
#include <openssl/sha.h> // For SHA256 hashing

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define MAX_HASHED_PASSWORD_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char hashed_password[MAX_HASHED_PASSWORD_LENGTH];
} User;

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void register_user(const char *username, const char *password) {
    User user;
    strncpy(user.username, username, MAX_USERNAME_LENGTH - 1);
    user.username[MAX_USERNAME_LENGTH - 1] = '\0';

    hash_password(password, user.hashed_password);

    // Simulate database insertion
    printf("Registering user:\n");
    printf("Username: %s\n", user.username);
    printf("Hashed Password: %s\n", user.hashed_password);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    register_user(username, password);

    return 0;
}