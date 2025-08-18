#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void showLogin() {
    printf("Login Page\n");
    printf("Enter Username: ");
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[50], password[50];
    int attempts = 0;

    while (attempts < 3) {
        showLogin();
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            showDashboard();
            return 0;
        } else {
            printf("Incorrect username or password. Please try again.\n");
            attempts++;
        }
    }

    printf("Too many failed attempts. Exiting...\n");
    return 1;
}