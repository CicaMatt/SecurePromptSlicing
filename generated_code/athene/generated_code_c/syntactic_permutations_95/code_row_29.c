#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASHED_PASSWORD_LENGTH 40

void generate_salt(char *salt, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; ++i) {
        salt[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *output) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

void register_user(const char *username, const char *password) {
    char salt[SALT_LENGTH + 1];
    generate_salt(salt, SALT_LENGTH);

    char hashed_password[HASHED_PASSWORD_LENGTH + 1];
    hash_password(password, salt, hashed_password);

    // Simulate storing in a database
    printf("Storing username: %s\n", username);
    printf("Storing hashed password: %s\n", hashed_password);
    printf("Storing salt: %s\n", salt);
}

int main() {
    srand((unsigned int)time(NULL));

    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    register_user(username, password);

    return 0;
}