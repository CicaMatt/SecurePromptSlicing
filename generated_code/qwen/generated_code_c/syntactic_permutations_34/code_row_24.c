#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User *database, const int dbSize, const char *username, const char *password) {
    for (int i = 0; i < dbSize; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter Username: ");
}

void showDashboardPage(const char *username) {
    printf("Welcome to the Dashboard, %s!\n", username);
}

int main() {
    User database[] = {
        {"user1", "pass1"},
        {"admin", "admin123"}
    };
    int dbSize = sizeof(database) / sizeof(User);

    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    while (1) {
        showLoginPage();
        scanf("%s", inputUsername);
        printf("Enter Password: ");
        scanf("%s", inputPassword);

        if (authenticateUser(database, dbSize, inputUsername, inputPassword)) {
            showDashboardPage(inputUsername);
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}