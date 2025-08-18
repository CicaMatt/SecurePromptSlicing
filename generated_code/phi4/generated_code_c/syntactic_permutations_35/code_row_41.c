#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int user_count = 0;

void initialize_users() {
    strcpy(users[user_count].username, "user1");
    strcpy(users[user_count].password, "pass1");
    user_count++;

    strcpy(users[user_count].username, "user2");
    strcpy(users[user_count].password, "pass2");
    user_count++;
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
    }
}

int main() {
    initialize_users();

    printf("Enter username: ");
    char username[50];
    scanf("%49s", username);

    printf("Enter password: ");
    char password[50];
    scanf("%49s", password);

    login(username, password);

    return 0;
}