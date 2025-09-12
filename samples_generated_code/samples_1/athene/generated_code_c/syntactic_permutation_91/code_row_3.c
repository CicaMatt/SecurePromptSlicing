#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define HASH_LENGTH 64

typedef struct {
    char username[USERNAME_MAX];
    char password_hash[HASH_LENGTH + 1];
} User;

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

void register_user(const char *username, const char *password) {
    User user;
    strncpy(user.username, username, USERNAME_MAX - 1);
    hash_password(password, user.password_hash);

    // Simulate database insertion
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", user.username, user.password_hash);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}