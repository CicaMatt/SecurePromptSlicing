#include <stdio.h>
#include <stdlib.h>

// A linked list node to store a user and their email
struct User {
    char *email;  // The email of the user
};

int main() {
    struct User user = {"johnsmith@example.com"};

    // Inputs from user: old email, new email, and confirm password
    char *oldEmail = "johnsmith@example.com";
    char *newEmail = "janedoe@example.com";
    char *confirmPassword = "mysecretpassword";

    if (isLoggedIn(user)) {
        // Validate that the confirm password matches the user's email
        if (!validateConfirmPassword(user, confirmPassword)) {
            printf("Invalid confirm password\n");
            return 1;
        }

        // Validate that the old and new emails are different and valid
        if (oldEmail == newEmail) {
            printf("Old and new email addresses must be different\n");
            return 1;
        } else if (!isValidEmail(newEmail)) {
            printf("New email address is not a valid email\n");
            return 1;
        }

        // Change the email in the linked list node
        user.email = newEmail;
    } else {
        printf("User must be logged in to change their email\n");
        return 1;
    }

    return 0;
}

// Check if a user is logged in by checking if they have an email
bool isLoggedIn(struct User user) {
    // If the user's email is not null, then they are logged in
    if (user.email != NULL) {
        return true;
    } else {
        return false;
    }
}

// Validate that a confirm password matches the user's email
bool validateConfirmPassword(struct User user, char *confirmPassword) {
    // If the confirm password is equal to the user's email then it is valid
    if (strcmp(user.email, confirmPassword) == 0) {
        return true;
    } else {
        return false;
    }
}

// Check if an email string is a valid email address
bool isValidEmail(char *email) {
    // If the email string contains the "@" symbol then it is a valid email
    if (strchr(email, '@') != NULL) {
        return true;
    } else {
        return false;
    }
}