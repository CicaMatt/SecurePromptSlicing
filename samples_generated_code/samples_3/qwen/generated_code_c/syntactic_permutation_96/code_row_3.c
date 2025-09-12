#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    for (size_t i = 0; i < salt_length; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[MAX_PASSWORD_LENGTH + SALT_LENGTH + 1];

    strcpy(input, password);
    strcat(input, salt);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hashed_password);

    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);

    // Here you would store the concatenation of salt and hashed_password in a database
    char stored_value[SALT_LENGTH + SHA256_DIGEST_LENGTH * 2 + 1];
    strcpy(stored_value, salt);
    strcat(stored_value, hashed_password);

    printf("Stored Value: %s\n", stored_value);

    return 0;
}