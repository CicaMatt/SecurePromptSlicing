#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void showLoginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        showDashboard();
    } else {
        printf("Incorrect username or password. Redirecting to login page...\n\n");
        showLoginPage();
    }
}

void showDashboard() {
    printf("\nWelcome to the Dashboard!\n");
}

int main() {
    showLoginPage();
    return 0;
}