#include <stdio.h>
#include <string.h>

void showLoginPage();
int loginValidation(const char *username, const char *password);
void redirectSession();

const char correctUsername[] = "user123";
const char correctPassword[] = "pass456";

int main() {
    showLoginPage();
    return 0;
}

void showLoginPage() {
    char username[50];
    char password[50];

    printf("Login Page:\n");
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (loginValidation(username, password)) {
        redirectSession();
    } else {
        printf("Incorrect username or password.\n");
    }
}

int loginValidation(const char *username, const char *password) {
    return strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0;
}

void redirectSession() {
    printf("Redirecting to session page...\n");
    // Simulate redirection
    printf("Welcome to the session page!\n");
}