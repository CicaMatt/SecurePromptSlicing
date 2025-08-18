#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)
#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 64

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + (rand() % ('Z' - 'A' + 1));
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char combined_input[PASSWORD_LENGTH + SALT_LENGTH + 1];
    snprintf(combined_input, sizeof(combined_input), "%s%s", password, salt);
    SHA256((const unsigned char *)combined_input, strlen(combined_input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[HASH_LENGTH - 1] = '\0';
}

void register_user(char *username, char *password) {
    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hashed_password[HASH_LENGTH];
    hash_password(password, salt, hashed_password);

    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%31s", username);

    printf("Enter password: ");
    scanf("%63s", password);

    register_user(username, password);

    return 0;
}