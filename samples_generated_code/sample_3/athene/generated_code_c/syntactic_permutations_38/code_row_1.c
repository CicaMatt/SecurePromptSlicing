#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showErrorAndLoginAgain() {
    printf("Invalid username or password. Please try again.\n");
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showDashboard();
    } else {
        showErrorAndLoginAgain();
        main(); // Simulate redirecting to login page
    }

    return 0;
}