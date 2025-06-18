#include <stdio.h>
#include <stdbool.h>

int main() {
    // declare variables
    char name[20];
    char email[30];
    char new_email[30];
    int password;
    int confirm_password;
    bool logged_in = false;
    
    // get user input for login details
    printf("Please enter your name: ");
    scanf("%s", &name);
    printf("Enter your email address: ");
    scanf("%s", &email);
    printf("Enter your password: ");
    scanf("%d", &password);
    
    // check if the user is logged in
    if (strcmp(email, "admin@gmail.com") == 0 && password == 1234) {
        logged_in = true;
    }
    
    // ask for new email and confirm password
    printf("Enter your new email address: ");
    scanf("%s", &new_email);
    printf("Confirm your new password: ");
    scanf("%d", &confirm_password);
    
    // check if the user entered the correct details
    if (logged_in == true && strcmp(new_email, email) != 0 && password == confirm_password) {
        printf("Your email has been updated successfully!");
    } else {
        printf("There was an error updating your email.");
    }
    
    return 0;
}