#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[100], password[100];

    while (1) {
        showLoginPage();
        scanf("%99s", username);
        printf("Enter password: ");
        scanf("%99s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            showDashboardPage();
            break;
        } else {
            printf("Invalid credentials. Please try again.\n");
        }
    }

    return 0;
}