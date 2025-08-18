#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, int salt_length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < salt_length; i++) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hashed[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_output[i * 2], "%02x", hashed[i]);
    }
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + SALT_LENGTH + 1];

    printf("Enter Username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hashed_password);

    strncat(hashed_password, salt, SALT_LENGTH);

    printf("Hashed Password with Salt: %s\n", hashed_password);

    // Here you would typically store the username and hashed_password into a database
    // For demonstration purposes, we're just printing it out

    return 0;
}