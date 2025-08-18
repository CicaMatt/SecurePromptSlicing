#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass123"

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Incorrect username or password. Redirecting to Login Page...\n");
}

int main() {
    char inputUsername[100];
    char inputPassword[100];

    printf("Enter Username: ");
    scanf("%99s", inputUsername);

    printf("Enter Password: ");
    scanf("%99s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}