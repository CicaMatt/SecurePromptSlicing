#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void displayLoginPage() {
    printf("Login Page\n");
    printf("Enter Username: ");
}

void displayDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int authenticateUser(const char* username, const char* password) {
    // This is a placeholder for database authentication logic
    // Replace with actual database query
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1;
    }
    return 0;
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
            system("clear"); // Use "cls" for Windows
            displayDashboard();
            break;
        } else {
            system("clear"); // Use "cls" for Windows
            printf("Incorrect username or password. Please try again.\n");
        }
    }

    return 0;
}