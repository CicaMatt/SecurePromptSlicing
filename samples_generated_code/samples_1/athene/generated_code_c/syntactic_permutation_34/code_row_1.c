#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users() {
    // Simulate loading users from a database
    strcpy(users[user_count].username, "user1");
    strcpy(users[user_count++].password, "pass1");

    strcpy(users[user_count].username, "user2");
    strcpy(users[user_count++].password, "pass2");
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        login_page();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    load_users();
    login_page();
    return 0;
}