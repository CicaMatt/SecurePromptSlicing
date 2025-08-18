#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define HASHED_PASSWORD_LENGTH 64

typedef struct {
    char username[USERNAME_MAX_LENGTH];
    char password_hash[HASHED_PASSWORD_LENGTH];
} User;

void hash_password(const char *password, unsigned char output[HASHED_PASSWORD_LENGTH]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

void register_user(const User *user) {
    FILE *db = fopen("users.db", "a");
    if (!db) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%s\n", user->username, user->password_hash);
    fclose(db);
}

int main() {
    User user;
    printf("Enter username: ");
    scanf("%49s", user.username);

    char password[PASSWORD_MAX_LENGTH];
    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, user.password_hash);

    register_user(&user);
    printf("User registered successfully.\n");
    return 0;
}