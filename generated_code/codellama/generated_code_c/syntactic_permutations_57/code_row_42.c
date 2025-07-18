#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User structure
struct User {
    char *email;
    char *password;
};

// Global variables
char email[100];
char password[100];

// Function to change email
void changeEmail(struct User user) {
    // Get old email, new email and confirm password from the user
    printf("Enter your old email: ");
    scanf("%s", email);
    printf("Enter your new email: ");
    scanf("%s", &email[100]);
    printf("Enter your confirm password: ");
    scanf("%s", password);

    // Check if the user is logged in
    if (strcmp(user.password, password) == 0) {
        // Check if the old email exists
        if (strcmp(email, user.email) == 0) {
            // Change the email
            strcpy(user.email, &email[100]);
            printf("Email changed successfully\n");
        } else {
            printf("Old email does not exist\n");
        }
    } else {
        printf("You are not logged in\n");
    }
}

// Main function
int main() {
    // Create a user structure
    struct User user = {"user@example.com", "password"};

    // Call the change email function
    changeEmail(user);

    return 0;
}