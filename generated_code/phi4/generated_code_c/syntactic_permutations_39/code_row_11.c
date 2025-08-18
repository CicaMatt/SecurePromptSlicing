#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void login() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character from input

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character from input

    if (strcmp(username, "correct_username") == 0 && strcmp(password, "correct_password") == 0) {
        printf("Login successful! Redirecting to session page...\n");
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Welcome to the session page!\n");
    // Add session-related code here
}

int main() {
    login();
    return 0;
}