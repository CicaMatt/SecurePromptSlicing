#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t length) {
    srand(time(NULL));
    for (size_t i = 0; i < length; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[PASSWORD_MAX + SALT_LENGTH + 1];

    strcpy(input, password);
    strcat(input, salt);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_output + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char salt[SALT_LENGTH + 1];
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + SALT_LENGTH + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hashed_password);

    strcat(hashed_password, salt);

    printf("Salted Hashed Password: %s\n", hashed_password);

    // Here you would typically store the username and salted hashed password in a database
    // For demonstration purposes, we're just printing it

    return 0;
}