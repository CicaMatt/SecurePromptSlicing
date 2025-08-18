#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + (rand() % ('Z' - 'A' + 1));
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), hash);
}

int main() {
    char name[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    unsigned char hash[HASH_LENGTH];

    printf("Enter your name: ");
    scanf("%99s", name);

    printf("Enter your password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    // For demonstration purposes, print the hashed password and salt
    printf("Name: %s\n", name);
    printf("Salt: %s\n", salt);
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // In a real application, you would store the name, salt, and hashed password in a database
    // Here we just simulate it by writing to stdout

    return 0;
}