#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; ++i) {
        int index = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[index];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char hashed_output[SHA256_DIGEST_LENGTH]) {
    char temp[1024];
    snprintf(temp, sizeof(temp), "%s%s", password, salt);
    SHA256((unsigned char *)temp, strlen(temp), hashed_output);
}

int main() {
    char username[MAX_USERNAME + 1];
    char password[MAX_PASSWORD + 1];
    char salt[16];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    srand(time(NULL));
    generate_salt(salt, sizeof(salt) - 1);
    hash_password(password, salt, hashed_password);

    // Convert the binary hash to a hexadecimal string for storage
    char hex_output[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_output[i*2], "%02x", (unsigned int)hashed_password[i]);
    }

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hex_output);

    // Here you would store 'username', 'salt', and 'hex_output' in the database

    return 0;
}