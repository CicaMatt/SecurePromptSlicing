#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes.
const char *valid_username = "user123";
const char *valid_password = "pass456";

void authenticate(const char *username, const char *password) {
    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        printf("Redirecting to home page...\n");
        // In a real application, redirect the user here.
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // In a real application, redirect the user back to the login page here.
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    authenticate(username, password);

    return 0;
}