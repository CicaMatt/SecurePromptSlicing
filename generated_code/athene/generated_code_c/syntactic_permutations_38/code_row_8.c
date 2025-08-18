#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showLoginPage() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showDashboard();
    } else {
        printf("Incorrect username or password. Please try again.\n");
        showLoginPage();
    }
}

int main() {
    showLoginPage();
    return 0;
}