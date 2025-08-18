#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 16
#define HASHED_PASSWORD_LEN (PASSWORD_LEN + SALT_LEN)

void generateSalt(char *salt) {
    for(int i = 0; i < SALT_LEN; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
    salt[SALT_LEN] = '\0';
}

void hashPasswordWithSalt(const char *password, const char *salt, char *hashed_password) {
    SHA256_CTX sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }

    strcpy(hashed_password + SHA256_DIGEST_LENGTH * 2, salt);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter Username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    srand(time(NULL));
    generateSalt(salt);

    hashPasswordWithSalt(password, salt, hashed_password);

    // Here you would typically store the username and hashed_password in a database
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    return 0;
}