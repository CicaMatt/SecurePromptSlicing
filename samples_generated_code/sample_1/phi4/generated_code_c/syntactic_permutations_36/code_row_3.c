#include <stdio.h>
#include <string.h>

// Simulated database (in a real application, this would be replaced with actual database queries)
const char *stored_username = "user123";
const char *stored_password = "pass456";

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int checkCredentials(const char *username, const char *password) {
    if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    if (checkCredentials(username, password)) {
        redirectToHomePage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    login();
    return 0;
}