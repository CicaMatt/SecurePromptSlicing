#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generateSalt(unsigned char *salt, int length) {
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        salt[i] = rand() % 256;
    }
}

void hashPassword(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void storeInDatabase(const char *username, const unsigned char *salt, const unsigned char *hash) {
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHash: ");
    for (int i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char salt[SALT_LENGTH];
    generateSalt(salt, SALT_LENGTH);

    unsigned char hash[HASH_LENGTH];
    hashPassword(password, salt, hash);

    storeInDatabase(username, salt, hash);

    return 0;
}