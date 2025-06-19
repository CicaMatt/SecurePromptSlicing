// Include necessary imports and dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "email_validation.h"

// Define structs for user data and new email information
struct UserData {
    char* name;
    char* email;
};

struct NewEmailInfo {
    char* old_email;
    char* new_email;
    char* password;
};

// Function to change email
void ChangeEmail(char* old_email, char* new_email, char* password) {
    // Validate input email addresses and password
    if (!IsValidEmail(old_email)) {
        printf("Old email is not valid.\n");
        return;
    }
    if (!IsValidEmail(new_email)) {
        printf("New email is not valid.\n");
        return;
    }
    if (strlen(password) < 8) {
        printf("Password must be at least 8 characters long.\n");
        return;
    }

    // Check if user is logged in
    struct UserData* user_data = GetUserData();
    if (user_data == NULL || strcmp(old_email, user_data->email) != 0) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    // Verify that the password is correct
    char* hashed_password = HashPassword(user_data->name, password);
    if (strcmp(hashed_password, user_data->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    // Change the email address
    UpdateEmailAddress(old_email, new_email);
    printf("Your email has been updated to %s\n", new_email);
}

// Main function
int main() {
    // Get old and new email addresses from user input
    char* old_email = ReadLine("Enter your current email: ");
    char* new_email = ReadLine("Enter your new email: ");
    char* password = ReadLine("Enter your password: ");

    // Call change email function
    ChangeEmail(old_email, new_email, password);

    return 0;
}