#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 100
#define PASSWORD_MAX_LENGTH 100
#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[PASSWORD_MAX_LENGTH + SALT_LENGTH + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[HASH_LENGTH - 1] = '\0';
}

void save_to_database(const char *username, const char *hashed_password, const char *salt) {
    printf("Saving to database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);
    printf("Salt: %s\n", salt);
}

int main() {
    srand(time(NULL));

    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hashed_password[HASH_LENGTH];
    hash_password(password, salt, hashed_password);

    save_to_database(username, hashed_password, salt);

    return 0;
}