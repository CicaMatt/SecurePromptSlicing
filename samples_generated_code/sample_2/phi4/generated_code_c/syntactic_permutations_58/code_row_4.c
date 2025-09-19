#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // Include space for null terminator
} User;

// Global variable to simulate a logged-in user
User loggedInUser = {"user123", "oldemail@example.com", "password123"};

int authenticate(int oldEmailEntered, const char* enteredOldEmail, const char* enteredPassword) {
    if (loggedInUser.email == NULL || strcmp(loggedInUser.email, enteredOldEmail) != 0) {
        printf("Incorrect old email.\n");
        return 0;
    }
    if (strcmp(loggedInUser.password, enteredPassword) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }
    return 1; // Authentication successful
}

void changeEmail(const char* newEmail) {
    strcpy(loggedInUser.email, newEmail);
    printf("Email successfully changed to %s\n", loggedInUser.email);
}

int main() {
    char enteredOldEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[PASSWORD_LENGTH + 1];
    char newEmail[MAX_EMAIL_LENGTH];

    // Simulate user input
    printf("Enter your old email: ");
    scanf("%99s", enteredOldEmail); // Use %99s to prevent buffer overflow

    printf("Enter your password: ");
    scanf("%20s", enteredPassword);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    if (authenticate(1, enteredOldEmail, enteredPassword)) {
        changeEmail(newEmail);
    } else {
        printf("Failed to change email.\n");
    }

    return 0;
}