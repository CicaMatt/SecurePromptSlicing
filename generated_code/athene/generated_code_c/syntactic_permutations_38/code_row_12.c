#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showLoginPage() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showDashboard();
    } else {
        printf("Incorrect username or password. Please try again.\n");
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