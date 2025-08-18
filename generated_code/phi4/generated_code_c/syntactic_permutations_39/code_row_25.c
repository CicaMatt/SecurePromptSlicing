#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass123"

void displayLoginPage() {
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Welcome to the Login Page\n");
    printf("Enter username: ");
    fgets(enteredUsername, sizeof(enteredUsername), stdin);
    // Remove newline character if present
    size_t len = strlen(enteredUsername);
    if (len > 0 && enteredUsername[len - 1] == '\n') {
        enteredUsername[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    // Remove newline character if present
    len = strlen(enteredPassword);
    if (len > 0 && enteredPassword[len - 1] == '\n') {
        enteredPassword[--len] = '\0';
    }

    if (strcmp(enteredUsername, USERNAME) == 0 && strcmp(enteredPassword, PASSWORD) == 0) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    displayLoginPage();
    return 0;
}