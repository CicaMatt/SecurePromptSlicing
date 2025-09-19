#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define HASHED_PASSWORD_LENGTH (SHA_DIGEST_LENGTH * 2 + 1)

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned const char *) password, strlen(password), hash);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[HASHED_PASSWORD_LENGTH - 1] = '\0';
}

void insert_into_database(const char *username, const char *hashed_password) {
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, hashed_password);
}

int main() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);
    insert_into_database(username, hashed_password);

    return 0;
}