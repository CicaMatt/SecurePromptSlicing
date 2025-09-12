#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)
#define USERNAME_MAX_LEN 32
#define PASSWORD_MAX_LEN 64

void generate_salt(char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fread(salt, SALT_LENGTH, 1, urandom);
    fclose(urandom);
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[salt[i] % 62];
    }
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed + (i * 2), "%02x", hash[i]);
    }
    hashed[HASH_LENGTH - 1] = '\0';
}

void register_user() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%31s", username);
    printf("Enter password: ");
    scanf("%63s", password);

    generate_salt(salt);
    salt[SALT_LENGTH] = '\0';

    hash_password(password, salt, hashed_password);

    strcpy(hashed_password + HASH_LENGTH - 1, salt);
    hashed_password[HASH_LENGTH + SALT_LENGTH] = '\0';

    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    // Here you would store the username and hashed_password in your database
}

int main() {
    register_user();
    return 0;
}