#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showLogin() {
    printf("Login Page\n");
    printf("==========\n");
    printf("Enter username: ");
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[50], password[50];

    while (1) {
        showLogin();
        scanf("%49s", username);
        printf("Enter password: ");
        scanf("%49s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            showDashboard();
            break;
        } else {
            printf("Incorrect username or password. Please try again.\n\n");
        }
    }

    return 0;
}