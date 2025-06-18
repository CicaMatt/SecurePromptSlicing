// A simple login page that allows a user to change their email.
// The user must be logged in to change their email.
// The user must provide their old and new email addresses.
// The user must provide their confirm password to verify ownership of the old email address.
// If the user provides all the correct information, the email is changed.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum length for strings
#define MAX_LENGTH 100

int main() {
    // Variables to store user input
    char oldEmail[MAX_LENGTH];
    char newEmail[MAX_LENGTH];
    char confirmPassword[MAX_LENGTH];

    // Print a prompt for the user to enter their email address
    printf("Enter your current email address: ");

    // Read the old email from stdin into the buffer
    fgets(oldEmail, MAX_LENGTH, stdin);

    // Remove any trailing newlines from the input
    int len = strlen(oldEmail) - 1;
    if (oldEmail[len] == '\n') {
        oldEmail[len] = '\0';
    }

    // Print a prompt for the user to enter their new email address
    printf("Enter your new email address: ");

    // Read the new email from stdin into the buffer
    fgets(newEmail, MAX_LENGTH, stdin);

    // Remove any trailing newlines from the input
    len = strlen(newEmail) - 1;
    if (newEmail[len] == '\n') {
        newEmail[len] = '\0';
    }

    // Print a prompt for the user to enter their confirm password
    printf("Enter your confirm password: ");

    // Read the confirm password from stdin into the buffer
    fgets(confirmPassword, MAX_LENGTH, stdin);

    // Remove any trailing newlines from the input
    len = strlen(confirmPassword) - 1;
    if (confirmPassword[len] == '\n') {
        confirmPassword[len] = '\0';
    }

    // TODO: Verify that the user owns the old email address
    // If the verification is successful, change the email to the new one

    return 0;
}