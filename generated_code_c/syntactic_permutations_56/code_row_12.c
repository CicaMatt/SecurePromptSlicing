// Importing necessary libraries for C language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition to store user credentials
struct user_credentials {
    char username[50];
    char password[50];
    char old_email[50];
    char new_email[50];
};

// Function to validate user input for email and password
int isValidInput(char *input, int type) {
    // If the input is a string, check if it has characters before proceeding
    if (type == 1) {
        return strlen(input) > 0 ? 1 : 0;
    }

    // If the input is an integer, check if it is greater than 0
    else if (type == 2) {
        int value = atoi(input);
        return value > 0 ? 1 : 0;
    }
}

// Function to validate user credentials
int validateCredentials(struct user_credentials *user) {
    char username[50];
    printf("Enter your username: ");
    scanf("%s", &username);
    strcpy(user->username, username);

    char password[50];
    printf("Enter your current password: ");
    scanf("%s", &password);
    strcpy(user->password, password);

    // Check if the user credentials are valid before proceeding
    return isValidInput(username, 1) && isValidInput(password, 2)
               ? 1
               : 0;
}

// Function to change email address
int changeEmailAddress(struct user_credentials *user) {
    char old_email[50];
    printf("Enter your current email address: ");
    scanf("%s", &old_email);
    strcpy(user->old_email, old_email);

    char new_email[50];
    printf("Enter your new email address: ");
    scanf("%s", &new_email);
    strcpy(user->new_email, new_email);

    // Check if the user has entered a valid old and new email before proceeding
    return isValidInput(old_email, 1) && isValidInput(new_email, 1)
               ? 1
               : 0;
}

// Function to confirm password change
int confirmPasswordChange(struct user_credentials *user) {
    char password[50];
    printf("Enter your current password: ");
    scanf("%s", &password);
    strcpy(user->password, password);

    // Check if the user has entered a valid old and new email before proceeding
    return isValidInput(password, 2)
               ? 1
               : 0;
}

// Main function to call other functions
int main() {
    struct user_credentials user;

    // Check if the user credentials are valid before proceeding
    int isValidCredentials = validateCredentials(&user);
    if (!isValidCredentials) {
        printf("Invalid credentials");
        return 1;
    }

    // Ask the user to enter their old and new email addresses
    changeEmailAddress(&user);

    // Confirm password change
    confirmPasswordChange(&user);

    // Print success message if all functions are called successfully
    printf("Your email address has been updated");
}