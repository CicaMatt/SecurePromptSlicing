#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to Login Page...\n");
}

int main() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    // Hardcoded valid credentials
    const char* correctUsername = "user";
    const char* correctPassword = "pass123";

    printf("Enter Username: ");
    fgets(username, MAX_LEN, stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter Password: ");
    fgets(password, MAX_LEN, stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}