#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64

void generate_salt(char *salt, size_t length) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

void store_user(const char *username, const char *hashed_password, const char *salt) {
    FILE *file = fopen("users.db", "a");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    fprintf(file, "%s:%s:%s\n", username, hashed_password, salt);
    fclose(file);
}

int main() {
    char username[256], password[256];
    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt, SALT_LENGTH);

    char hashed_password[HASH_LENGTH + 1];
    hash_password(password, salt, hashed_password);

    store_user(username, hashed_password, salt);

    printf("User registered successfully.\n");
    return 0;
}