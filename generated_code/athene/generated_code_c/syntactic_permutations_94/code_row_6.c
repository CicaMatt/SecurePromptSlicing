#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char *username;
    char *password_hash;
} User;

void hash_password(const char *password, const char *salt, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, strlen(salt));
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
}

void insert_user_into_database(const User *user) {
    // This is a placeholder function to represent database insertion.
    // In a real application, you would use SQL or an ORM to insert the user into your database.
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", user->username, user->password_hash);
}

int main() {
    const char *username = "exampleUser";
    const char *password = "securePassword123";
    const char *salt = "randomSalt"; // In practice, use a secure random salt for each password.

    User user;
    user.username = username;

    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, salt, password_hash);
    user.password_hash = password_hash;

    insert_user_into_database(&user);

    return 0;
}