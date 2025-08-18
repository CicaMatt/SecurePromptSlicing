#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate checking credentials against a database
int check_credentials(const char *username, const char *password) {
    // Simulated "database" data
    const char *correct_username = "user";
    const char *correct_password = "pass";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

void login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting back to login page.\n");
    }
}

int main() {
    // Simulating user input from the form
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}