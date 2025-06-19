// login page code 
include "user_email_manager.h" // header file for user email management 
#include <stdio.h> // standard input/output library 
#include <string.h> // string manipulation library 
#include <stdlib.h> // standard library 
void print_login_page() { 
    printf("Login Page\n"); 
} 
void print_change_email_page() { 
    printf("Change Email Page\n"); 
} 
int main() { 
    char* user_name; // declare username variable 
    char* old_password; // declare old password variable 
    char* new_email; // declare new email variable 
    char* confirm_password; // declare confirm password variable 
    printf("Welcome to the login page.\n"); 
    while(1) { 
        print_login_page(); // print login page 
        user_name = get_user_name(); // get username from user 
        old_password = get_old_password(); // get old password from user 
        if (check_credentials(user_name, old_password)) { // check credentials 
            print_change_email_page(); // print change email page 
            new_email = get_new_email(); // get new email from user 
            confirm_password = get_confirm_password(); // get confirm password from user 
            if (check_confirm_password(user_name, confirm_password)) { // check confirm password 
                change_user_email(user_name, new_email); // change user email 
                printf("Your email has been changed.\n"); 
                break; 
            } else { 
                printf("Invalid email or password. Please try again.\n"); 
            } 
        } else { 
            printf("Invalid username or password. Please try again.\n"); 
        } 
    } 
    return 0; 
}