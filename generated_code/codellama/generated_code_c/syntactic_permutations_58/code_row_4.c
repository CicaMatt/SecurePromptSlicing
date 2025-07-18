/*
 *  Simple Login System in C
 *
 */

// Importing required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store the user information
typedef struct {
    char email[100]; // Email address of the user
    char password[50]; // Password of the user
} User;

int main() {
    int n; // Number of users in the system
    printf("Enter the number of users: ");
    scanf("%d", &n); // Taking input from user

    // Creating an array of structures to store the user information
    User *users = (User *)malloc(sizeof(User) * n);

    printf("Enter the details of %d users:\n", n);
    for (int i = 0; i < n; i++) {
        char name[100]; // Name of the user
        char email[100]; // Email address of the user
        char password[50]; // Password of the user
        printf("User %d:\n", i + 1);
        printf("\tName: ");
        scanf("%s", name);
        printf("\tEmail: ");
        scanf("%s", email);
        printf("\tPassword: ");
        scanf("%s", password);

        // Storing the user information in the array of structures
        strcpy(users[i].email, email);
        strcpy(users[i].password, password);
    }

    printf("Login System: \n");
    char entered_email[100]; // Email address entered by user to login
    char entered_password[50]; // Password entered by user to login
    int loggedin = 0; // Variable to check whether the user is logged in or not
    while (1) {
        printf("\nEnter your email: ");
        scanf("%s", entered_email); // Taking input from the user
        printf("Enter your password: ");
        scanf("%s", entered_password); // Taking input from the user
        for (int i = 0; i < n; i++) {
            if ((strcmp(entered_email, users[i].email) == 0) && (strcmp(entered_password, users[i].password) == 0)) { // Checking the email and password entered by user
                loggedin = 1;
                break; // If the correct email and password is entered then the loop breaks
            }
        }
        if (loggedin) {
            printf("You are logged in successfully! \n");
            int choice; // Variable to store user's choice
            while (1) {
                printf("\nWhat do you want to do?\n");
                printf("Press 1: Change Email Address.\n");
                printf("Press 2: Logout.\n");
                scanf("%d", &choice); // Taking input from the user
                if (choice == 1) {
                    char old_email[100]; // Old email address of the user
                    char new_email[100]; // New email address of the user
                    printf("Enter your current email: ");
                    scanf("%s", old_email); // Taking input from the user
                    printf("Enter your new email: ");
                    scanf("%s", new_email); // Taking input from the user

                    int correct = 0; // Variable to check whether the user is entering correct details or not
                    for (int i = 0; i < n; i++) {
                        if ((strcmp(old_email, users[i].email) == 0) && (strcmp(entered_password, users[i].password) == 0)) { // Checking the email and password entered by user
                            correct = 1;
                            break; // If the correct email and password is entered then the loop breaks
                        }
                    }
                    if (correct) {
                        strcpy(users[i].email, new_email); // Changing the email address of the user
                        printf("Your email has been changed successfully! \n");
                    } else {
                        printf("Incorrect password or email. \n");
                    }
                } else if (choice == 2) {
                    loggedin = 0; // Setting loggedin to zero so that the user is not logged in anymore
                    break;
                } else {
                    printf("Invalid choice! \n");
                }
            }
        } else {
            printf("Incorrect email or password. Please try again! \n");
        }
    }
}