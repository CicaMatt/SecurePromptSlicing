#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define HASH_LEN (SHA256_DIGEST_LENGTH * 2 + 1)

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

void insert_user_into_db(const char *username, const char *password_hash) {
    // This is a placeholder function. In real code, you would use an SQL query
    // to insert the username and password hash into your database.
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, password_hash);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char password_hash[HASH_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);
    insert_user_into_db(username, password_hash);

    return 0;
}