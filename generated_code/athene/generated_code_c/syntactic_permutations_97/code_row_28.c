#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USER 50
#define MAX_PASS 100
#define MAX_NAME 50
#define MAX_EMAIL 100

typedef struct {
    char username[MAX_USER];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

User users[100]; // Simulated database
int user_count = 0;

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int find_user(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (find_user(username)) {
        printf("Username already exists.\n");
        return;
    }

    User new_user;
    strncpy(new_user.username, username, MAX_USER - 1);
    hash_password(password, new_user.password_hash);

    users[user_count++] = new_user;
    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}