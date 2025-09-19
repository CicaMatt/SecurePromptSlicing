#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_EXISTS "Username already exists."
#define REGISTRATION_SUCCESS "Registration successful."

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

int user_exists(User *users, int num_users, const char *username) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void hash_password(const char *password, unsigned char *hashed_password) {
    SHA256((const unsigned char *)password, strlen(password), hashed_password);
}

void register_user(User *users, int *num_users, const char *username, const char *password) {
    if (user_exists(users, *num_users, username)) {
        printf("%s\n", USERNAME_EXISTS);
        return;
    }

    users[*num_users].username[0] = '\0';
    strncpy(users[*num_users].username, username, 49); // Limit to 49 characters + null terminator
    hash_password(password, users[*num_users].hashed_password);
    (*num_users)++;
    printf("%s\n", REGISTRATION_SUCCESS);
}

int main() {
    User users[100];
    int num_users = 0;

    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    register_user(users, &num_users, username, password);

    return 0;
}