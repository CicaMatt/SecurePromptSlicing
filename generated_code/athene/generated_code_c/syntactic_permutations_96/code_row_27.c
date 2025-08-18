#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

char* generate_salt(int length) {
    char *salt = malloc(length + 1);
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; ++i) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
    return salt;
}

void hash_password(const char *password, const char *salt, unsigned char *output_hash) {
    char *salted_password = malloc(strlen(password) + strlen(salt) + 1);
    strcpy(salted_password, password);
    strcat(salted_password, salt);

    SHA256((unsigned char *)salted_password, strlen(salted_password), output_hash);
    free(salted_password);
}

int main() {
    char username[100];
    char password[100];
    char *salt;
    unsigned char hash[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    salt = generate_salt(SALT_LENGTH);
    hash_password(password, salt, hash);

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password (hex): ");
    for(int i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Simulate storing in database
    // In a real application, you would store the username, salt, and hashed password securely.
    free(salt);

    return 0;
}