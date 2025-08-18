#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH * 2)

void generate_salt(char *salt, size_t salt_length) {
    for (size_t i = 0; i < salt_length; ++i) {
        salt[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"[rand() % 62];
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[PASSWORD_LEN + SALT_LEN + 1];

    snprintf(input, sizeof(input), "%s%s", password, salt);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN + SALT_LEN + 1];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hashed_password);

    snprintf(hashed_password + HASHED_PASSWORD_LEN, sizeof(salt) + 1, "%s", salt);

    printf("\nStored in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    return 0;
}