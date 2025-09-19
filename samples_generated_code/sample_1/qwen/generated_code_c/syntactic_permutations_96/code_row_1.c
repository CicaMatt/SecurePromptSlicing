#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt, int length) {
    for (int i = 0; i < length; i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char hash_buffer[HASH_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash_buffer, &sha256);

    for (int i = 0; i < HASH_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", hash_buffer[i]);
    }
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH];
    char hashed_password[(HASH_LENGTH * 2) + SALT_LENGTH + 1];

    printf("Enter Username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hashed_password);

    // Simulating storing salt and hashed password in the database
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);

    return 0;
}