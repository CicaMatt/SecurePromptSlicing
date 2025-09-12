#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define EMAIL_LEN 100

typedef struct {
    char username[USERNAME_LEN];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int find_user(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void register_user() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char first_name[NAME_LEN];
    char last_name[NAME_LEN];
    char email[EMAIL_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    if (find_user(username) != -1) {
        printf("Username already exists.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (user_count >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    strncpy(users[user_count].username, username, USERNAME_LEN - 1);
    memcpy(users[user_count].password_hash, password_hash, SHA256_DIGEST_LENGTH);
    user_count++;

    printf("Registration succeeded.\n");
}

int main() {
    register_user();
    return 0;
}