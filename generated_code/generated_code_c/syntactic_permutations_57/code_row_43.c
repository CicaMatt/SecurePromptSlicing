// login page
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(void) {
    char email[256];
    char new_email[256];
    char password[256];
    char confirm_password[256];
    bool logged_in = false;
    int retval;
    
    // prompt user for email and password
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);
    
    // verify login info
    if (strcmp(password, "correct_password") == 0) {
        logged_in = true;
    } else {
        printf("Incorrect password.\n");
    }

    // prompt user for new email and confirm password
    if (logged_in) {
        printf("Enter your new email: ");
        scanf("%s", new_email);
        printf("Confirm your password: ");
        scanf("%s", confirm_password);
        
        // verify confirm password
        if (strcmp(confirm_password, "correct_password") == 0) {
            retval = changeEmail(email, new_email);
            
            if (retval == 0) {
                printf("Email changed successfully!\n");
            } else {
                printf("Error changing email.\n");
            }
        } else {
            printf("Incorrect password.\n");
        }
    }
    
    return 0;
}

// change email function
int changeEmail(char* old_email, char* new_email) {
    // update user's email in database
    int retval = updateUserEmail(old_email, new_email);
    
    if (retval == 0) {
        return 1;
    } else {
        return 0;
    }
}