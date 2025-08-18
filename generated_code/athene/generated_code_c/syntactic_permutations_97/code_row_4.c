#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_INPUT 100
#define DB_SIZE 100

typedef struct {
    char username[MAX_INPUT];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

User db[DB_SIZE];
int user_count = 0;

void hash_password(const char *password, unsigned char *hash) {
    SHA256((unsigned char *)password, strlen(password), hash);
}

int username_exists(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(db[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_count >= DB_SIZE) {
        printf("Database full. Registration failed.\n");
        return;
    }

    if (username_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    User new_user;
    strncpy(new_user.username, username, MAX_INPUT - 1);
    hash_password(password, new_user.password_hash);

    db[user_count++] = new_user;

    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_INPUT], password[MAX_INPUT], first_name[MAX_INPUT], last_name[MAX_INPUT], email[MAX_INPUT];

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