#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define SALT_LEN 8
#define HASH_LEN 64
#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LEN; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LEN] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[128];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
}

void insert_into_db(const char *username, const char *hashed_password, const char *salt) {
    printf("INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%s', '%s');\n", 
           username, hashed_password, salt);
}

int main() {
    srand(time(NULL));

    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char salt[SALT_LEN + 1];
    char hashed_password[HASH_LEN + 1];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    insert_into_db(username, hashed_password, salt);

    return 0;
}