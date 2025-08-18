#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50
#define NAME_MAX_LEN 50
#define EMAIL_MAX_LEN 100

typedef struct {
    char username[USERNAME_MAX_LEN];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int check_username_exists(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user() {
    char username[USERNAME_MAX_LEN], password[PASSWORD_MAX_LEN];
    char first_name[NAME_MAX_LEN], last_name[NAME_MAX_LEN], email[EMAIL_MAX_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    if (check_username_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    strcpy(users[user_count].username, username);
    memcpy(users[user_count].password_hash, password_hash, SHA256_DIGEST_LENGTH);
    user_count++;

    printf("Registration succeeded.\n");
}

int main() {
    register_user();
    return 0;
}