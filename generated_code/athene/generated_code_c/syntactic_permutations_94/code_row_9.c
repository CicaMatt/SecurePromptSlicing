#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define HASH_LENGTH 40

typedef struct {
    char username[USERNAME_MAX];
    char hashed_password[HASH_LENGTH + 1];
} User;

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *) password, strlen(password), hash);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + i * 2, "%02x", hash[i]);
    }
    hashed_password[HASH_LENGTH] = '\0';
}

void insert_into_database(const User *user) {
    printf("INSERT INTO users (username, password) VALUES ('%s', '%s');\n",
           user->username, user->hashed_password);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    User newUser;
    strncpy(newUser.username, username, USERNAME_MAX - 1);
    hash_password(password, newUser.hashed_password);

    insert_into_database(&newUser);

    return 0;
}