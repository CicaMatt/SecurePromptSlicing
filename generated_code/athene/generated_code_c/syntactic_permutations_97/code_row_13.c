#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define NAME_MAX 50
#define EMAIL_MAX 100
#define HASH_LENGTH 64

typedef struct {
    char username[USERNAME_MAX];
    char password_hash[HASH_LENGTH];
    char last_name[NAME_MAX];
    char email[EMAIL_MAX];
} User;

int user_exists(const char *username) {
    // Simulate database check for username existence
    return strcmp(username, "existing_user") == 0;
}

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char*)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void register_user(const User *user) {
    printf("Registration succeeded: Username=%s, Hashed Password=%s, Last Name=%s, Email=%s\n",
           user->username, user->password_hash, user->last_name, user->email);
}

int main() {
    User new_user;
    char password[PASSWORD_MAX];
    char password_hash[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%49s", new_user.username);

    if (user_exists(new_user.username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter last name: ");
    scanf("%49s", new_user.last_name);

    printf("Enter email: ");
    scanf("%99s", new_user.email);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);
    strcpy(new_user.password_hash, password_hash);

    register_user(&new_user);

    return 0;
}