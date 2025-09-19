#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void showLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
    char username[50];
    scanf("%s", username);
    printf("Password: ");
    char password[50];
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
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