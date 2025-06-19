#include <stdio.h>
    #include <string.h>
    #include "email_handler.h"
    #include "login_manager.h"
    #include "user_details.h"

    int main() {
        char oldEmail[100];
        char newEmail[100];
        char confirmPassword[256];
        printf("Enter your old email: ");
        scanf("%s", oldEmail);

        if (isLoggedIn(oldEmail)) {
            printf("You are not logged in.");
        } else {
            printf("Enter new email: ");
            scanf("%s", newEmail);
            printf("Enter confirm password: ");
            scanf("%s", confirmPassword);
            if (validateUserDetails(oldEmail, confirmPassword)) {
                changeEmail(oldEmail, newEmail);
                printf("Email changed successfully.");
            } else {
                printf("Invalid email or password.");
            }
        }
    }

    #include <string.h>
    int isLoggedIn(char *email) {
        // implement code to check if user is logged in
        return 0;
    }

    #include <string.h>
    int validateUserDetails(char *oldEmail, char *confirmPassword) {
        // implement code to validate user details
        return 1;
    }

    #include <string.h>
    void changeEmail(char *oldEmail, char *newEmail) {
        // implement code to change email
    }