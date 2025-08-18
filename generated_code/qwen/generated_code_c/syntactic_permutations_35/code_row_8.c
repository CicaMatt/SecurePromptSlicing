#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP redirection here.
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP redirection here.
    }

    return 0;
}