#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8
#define HASH_LENGTH SHA256_DIGEST_LENGTH + SALT_LENGTH

void generate_salt(char *salt, int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        salt[i] = 'A' + rand() % ('z' - 'A');
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(sha256_hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", sha256_hash[i]);
    }
    strcat(hash, salt);
}

void register_user(const char *username, const char *password) {
    char salt[SALT_LENGTH + 1];
    char hash[HASH_LENGTH + 1];

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hash);

    // Simulate storing in a database
    printf("Storing user: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hash);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    register_user(username, password);

    return 0;
}