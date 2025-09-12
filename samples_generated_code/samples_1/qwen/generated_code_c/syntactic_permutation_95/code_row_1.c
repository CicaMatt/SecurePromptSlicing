#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    srand(time(NULL));
    for (size_t i = 0; i < salt_length; i++) {
        int random_char = rand() % 62;
        if (random_char < 10)
            salt[i] = '0' + random_char;
        else if (random_char < 36)
            salt[i] = 'A' + (random_char - 10);
        else
            salt[i] = 'a' + (random_char - 36);
    }
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(sha256_hash, &sha256);

    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", sha256_hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1] = {0};
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + SALT_LENGTH + 1] = {0};

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    strncat(hashed_password, salt, SALT_LENGTH);

    printf("Stored in database:\nUsername: %s\nPassword (Hashed + Salt): %s\n", username, hashed_password);

    return 0;
}