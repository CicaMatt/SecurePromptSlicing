#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

typedef struct {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} User;

User users[MAX_USERS] = {
    {"admin", "password"}, // Example user
    // Add more users if needed
};

int num_users = 1; // Number of users in the database

void login_page() {
    char username[USERNAME_MAX_LENGTH], password[PASSWORD_MAX_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    int found = 0;
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            found = 1;
            dashboard_page();
            break;
        }
    }

    if (!found) {
        printf("Invalid username or password. Redirecting to login page.\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
    // Add more dashboard functionality here
}

int main() {
    login_page();
    return 0;
}