#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid credentials! Redirecting back to Login Page...\n");
}

int main() {
    char correctUsername[MAX_LENGTH] = "admin";
    char correctPassword[MAX_LENGTH] = "password123";

    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Password: ");
    scanf("%99s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}