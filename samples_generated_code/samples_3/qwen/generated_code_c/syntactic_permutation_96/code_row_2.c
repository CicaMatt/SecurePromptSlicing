#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH * 2 + SALT_LEN)

void generate_salt(char* salt, size_t salt_length) {
    for (size_t i = 0; i < salt_length; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
    salt[salt_length] = '\0';
}

void hash_password(const char* password, const char* salt, char* hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strcat(hashed_password, salt);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN + 1];

    printf("Enter your username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, hashed_password);

    printf("Salted Hashed Password: %s\n", hashed_password);

    return 0;
}