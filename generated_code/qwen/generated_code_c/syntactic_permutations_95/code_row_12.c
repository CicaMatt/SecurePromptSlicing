#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH + SALT_LEN)

void generate_salt(unsigned char *salt) {
    srand(time(NULL));
    for(int i = 0; i < SALT_LEN; i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
    memcpy(hashed_password + SHA256_DIGEST_LENGTH, salt, SALT_LEN);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Here you would typically store the username and hashed_password in a database
    // For demonstration purposes, we'll just print them out
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: ");
    for(int i = 0; i < HASHED_PASSWORD_LEN; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}