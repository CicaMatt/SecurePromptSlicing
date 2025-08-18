#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showLoginPage() {
    char username[50], password[50];
    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showDashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        showLoginPage();
    }
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    showLoginPage();
    return 0;
}