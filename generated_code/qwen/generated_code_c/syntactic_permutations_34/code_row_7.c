#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database entry
const char *db_username = "admin";
const char *db_password = "password123";

void displayLoginPage() {
    printf("Login Page\n");
    printf("Enter Username: ");
}

void displayDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int authenticateUser(const char *username, const char *password) {
    return strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        displayLoginPage();
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);

        if (authenticateUser(username, password)) {
            displayDashboardPage();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}