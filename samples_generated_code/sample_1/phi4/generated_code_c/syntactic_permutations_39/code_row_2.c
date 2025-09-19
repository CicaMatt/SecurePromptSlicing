#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void showLoginPage();
void validateCredentials(const char* username, const char* password);
void redirectToSessionPage();

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Simple Login Page\n");
    printf("------------------\n");

    showLoginPage();

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    validateCredentials(username, password);

    return 0;
}

void showLoginPage() {
    // This function would ideally show a login form
    // Here it's just a placeholder since we're using console input.
}

void validateCredentials(const char* username, const char* password) {
    const char correctUsername[] = "user";
    const char correctPassword[] = "password";

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void redirectToSessionPage() {
    printf("Login successful! Redirecting to session page...\n");
    // In a real application, this would redirect the user
}