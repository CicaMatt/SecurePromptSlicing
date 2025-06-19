// Include necessary dependencies
    #include <stdio.h>
    #include <string.h>

    // Define constants for maximum input lengths
    #define MAX_EMAIL_LENGTH 50
    #define MAX_PASSWORD_LENGTH 20

    // Define variables for the user's old email, new email, and password
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Define a function to check if the user is logged in
    int isLoggedIn(char* email, char* password) {
        // Check if the email and password are correct
        if (strcmp(email, "admin@example.com") == 0 && strcmp(password, "password123") == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    // Define a function to change the user's email
    void changeEmail(char* oldEmail, char* newEmail) {
        // Check if the old email is correct
        if (strcmp(oldEmail, "admin@example.com") == 0) {
            // Change the email
            strcpy(oldEmail, newEmail);
            printf("Your email has been changed successfully.\n");
        } else {
            printf("Error: Incorrect old email.\n");
        }
    }

    int main() {
        // Ask the user to enter their old email
        printf("Enter your old email: ");
        fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);

        // Ask the user to enter their new email
        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);

        // Ask the user to enter their password
        printf("Enter your password: ");
        fgets(password, MAX_PASSWORD_LENGTH, stdin);

        // Check if the user is logged in
        if (isLoggedIn(oldEmail, password)) {
            // Change the email
            changeEmail(oldEmail, newEmail);
        } else {
            printf("Error: Incorrect old email or password.\n");
        }
    }