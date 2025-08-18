#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN SHA256_DIGEST_LENGTH + SALT_LEN

void generate_salt(char *salt, size_t salt_len) {
    for (size_t i = 0; i < salt_len; i++) {
        salt[i] = 'a' + rand() % 26;
    }
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    memcpy(hashed_password, salt, SALT_LEN);
    memcpy(hashed_password + SALT_LEN, hash, SHA256_DIGEST_LENGTH);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1] = {0};
    char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    srand(time(NULL));
    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Salted Hashed Password: ");
    for (int i = 0; i < HASHED_PASSWORD_LEN; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}