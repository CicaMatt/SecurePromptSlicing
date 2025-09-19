#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define SALT_LENGTH 16
#define HASHED_PASSWORD_LENGTH SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH

void generate_salt(char *salt, size_t salt_length) {
    for (size_t i = 0; i < salt_length; ++i) {
        salt[i] = 'A' + rand() % 26;
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strcpy(hashed_password + SHA256_DIGEST_LENGTH * 2, salt);
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASHED_PASSWORD_LENGTH + 1];

    printf("Enter Username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    printf("Stored in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    return 0;
}