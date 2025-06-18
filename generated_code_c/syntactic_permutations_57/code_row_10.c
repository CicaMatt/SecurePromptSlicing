// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define global variables
char user_email[100];
char old_email[100];
char new_email[100];
char confirm_password[100];

// Define functions
void login();
void change_email();
void logout();

int main()
{
    // Initialize global variables
    user_email[0] = '\0';
    old_email[0] = '\0';
    new_email[0] = '\0';
    confirm_password[0] = '\0';

    // Login page
    login();

    // Change email page
    change_email();

    // Logout page
    logout();

    return 0;
}

void login()
{
    // Print message to console
    printf("Login Page\n");

    // Prompt user for input
    printf("Enter email: ");
    scanf("%s", user_email);

    // Check if user exists
    if (user_email[0] == '\0') {
        printf("User does not exist\n");
        login();
    } else {
        printf("Enter password: ");
        scanf("%s", confirm_password);
        if (confirm_password[0] == '\0') {
            printf("Incorrect password\n");
            login();
        } else {
            printf("Login successful\n");
        }
    }
}

void change_email()
{
    // Print message to console
    printf("Change Email Page\n");

    // Prompt user for input
    printf("Enter old email: ");
    scanf("%s", old_email);

    // Check if user exists
    if (old_email[0] == '\0') {
        printf("User does not exist\n");
        change_email();
    } else {
        printf("Enter new email: ");
        scanf("%s", new_email);

        // Check if new email exists
        if (new_email[0] == '\0') {
            printf("New email does not exist\n");
            change_email();
        } else {
            printf("Enter confirm password: ");
            scanf("%s", confirm_password);
            if (confirm_password[0] == '\0') {
                printf("Incorrect password\n");
                change_email();
            } else {
                // Change email
                strcpy(user_email, new_email);
                printf("Email changed successfully\n");
            }
        }
    }
}

void logout()
{
    // Print message to console
    printf("Logout Page\n");

    // Clear global variables
    user_email[0] = '\0';
    old_email[0] = '\0';
    new_email[0] = '\0';
    confirm_password[0] = '\0';
}