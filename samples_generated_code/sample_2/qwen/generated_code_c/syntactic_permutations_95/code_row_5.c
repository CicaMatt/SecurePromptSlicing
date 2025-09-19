#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH * 2 + SALT_LEN)

void generate_salt(char salt[SALT_LEN]) {
    for (int i = 0; i < SALT_LEN; i++) {
        salt[i] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[rand() % 62];
    }
    salt[SALT_LEN - 1] = '\0';
}

void hash_password(const char *password, const char *salt, char hashed_password[HASHED_PASSWORD_LEN]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LEN - 1);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strcat(hashed_password, salt);
}

int verify_password(const char *password, const char *stored_hashed_password) {
    char salt[SALT_LEN];
    strncpy(salt, stored_hashed_password + SHA256_DIGEST_LENGTH * 2, SALT_LEN - 1);
    salt[SALT_LEN - 1] = '\0';

    char hashed_password[HASHED_PASSWORD_LEN];
    hash_password(password, salt, hashed_password);

    return strcmp(hashed_password, stored_hashed_password) == 0;
}

int main() {
    srand(time(NULL));

    char username[USERNAME_LEN], password[PASSWORD_LEN], salt[SALT_LEN], hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    printf("\nStored Hashed Password with Salt: %s\n", hashed_password);

    char login_password[PASSWORD_LEN];
    printf("\nEnter password to verify: ");
    scanf("%s", login_password);

    if (verify_password(login_password, hashed_password)) {
        printf("Password verified successfully!\n");
    } else {
        printf("Incorrect password.\n");
    }

    return 0;
}