#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 100
#define HASHED_PASSWORD_LEN 65

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void insert_into_database(const char *username, const char *hashed_password) {
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, hashed_password);
}

int main() {
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter username: ");
    if (scanf("%50s", username) != 1) return 1;

    printf("Enter password: ");
    if (scanf("%100s", password) != 1) return 1;

    hash_password(password, hashed_password);

    insert_into_database(username, hashed_password);

    return 0;
}