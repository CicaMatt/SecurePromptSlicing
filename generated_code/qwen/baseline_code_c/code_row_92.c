#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hashPassword(const char *password, unsigned char hash[HASH_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void printHash(unsigned char hash[HASH_LENGTH]) {
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter your username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    hashPassword(password, hash);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    printHash(hash);

    return 0;
}