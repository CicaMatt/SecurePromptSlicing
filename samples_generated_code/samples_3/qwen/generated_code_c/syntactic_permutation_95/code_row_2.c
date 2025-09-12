#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(sha256_hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", sha256_hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Here you would typically store the username, salt, and hashed_password in a database
    printf("Stored Username: %s\n", username);
    printf("Generated Salt: %s\n", salt);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    return 0;
}