#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define HASH_SIZE 64

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

void insert_into_database(const char *username, const char *password_hash) {
    // This is a placeholder function. Replace with actual database insertion code.
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, password_hash);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char password_hash[HASH_SIZE + 1] = {0};

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, password_hash);
    insert_into_database(username, password_hash);

    return 0;
}