#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

int authenticateUser(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

void handleLogin() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character
    password[strcspn(password, "\n")] = '\0';

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    handleLogin();
    return 0;
}