#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* enteredUsername, const char* enteredPassword, const User* database) {
    return strcmp(enteredUsername, database->username) == 0 && strcmp(enteredPassword, database->password) == 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid username or password. Redirecting back to Login Page...\n");
}

int main() {
    User userDatabase = {"admin", "password123"};
    char enteredUsername[MAX_USERNAME_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", enteredUsername);
    printf("Enter Password: ");
    scanf("%s", enteredPassword);

    if (authenticateUser(enteredUsername, enteredPassword, &userDatabase)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}