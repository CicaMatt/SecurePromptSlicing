#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt, int length) {
    for (int i = 0; i < length; i++) {
        salt[i] = (char)(rand() % 94 + 33); // ASCII printable characters
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char digest[HASH_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
    for (int i = 0; i < HASH_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    char salt[SALT_LENGTH + 1];
    char hash[HASH_LENGTH * 2 + SALT_LENGTH + 1]; // Hexadecimal representation of hash + salt

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hash);
    strcat(hash, salt); // Concatenate hash and salt

    printf("Stored in database: %s\n", hash);

    return 0;
}