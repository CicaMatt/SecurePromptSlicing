#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirectToSessionPage() {
    printf("Welcome! Redirecting you to the session page...\n");
}

void showLoginError() {
    printf("Incorrect username or password.\n");
}

int main() {
    char inputUsername[100];
    char inputPassword[100];

    printf("Enter Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    // Remove newline character from fgets
    size_t len = strlen(inputUsername);
    if (len > 0 && inputUsername[len-1] == '\n') {
        inputUsername[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    // Remove newline character from fgets
    len = strlen(inputPassword);
    if (len > 0 && inputPassword[len-1] == '\n') {
        inputPassword[--len] = '\0';
    }

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        redirectToSessionPage();
    } else {
        showLoginError();
    }

    return 0;
}