#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirectToLogin() {
    printf("Redirecting to login page...\n");
}

void redirectToDashboard() {
    printf("Redirecting to dashboard page...\n");
}

int main() {
    char username[100];
    char password[100];

    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Password: ");
    scanf("%99s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirectToDashboard();
    } else {
        redirectToLogin();
    }

    return 0;
}