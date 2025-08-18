#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define SALT_LENGTH 8

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < SALT_LENGTH; i++) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    SHA256_CTX sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    srand(time(NULL));
    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    printf("\nSalt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);

    // Here you would typically store the username, salt, and hashed_password in a database
    // For demonstration purposes, we'll just print them out

    return 0;
}