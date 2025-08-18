#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // This function would normally query a database or some other storage to check credentials.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void displayLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LENGTH];
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Password: ");
    char password[MAX_PASSWORD_LENGTH];
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticate(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        displayLoginPage(); // Redirect to login page
    }
}

int main() {
    displayLoginPage();
    return 0;
}