#include <stdio.h> //For printf()
#include <string.h> //For strcmp()
#include <stdlib.h> //For exit()
#define MAX 1024 //Max length of email and password strings

//Global variables for email and password (set to default)
char old_email[MAX] = "old@email.com";
char old_password[MAX] = "old_password";

int main() {
    char new_email[MAX]; //New email input by user
    char password[MAX]; //Password input by user
    int isLoggedIn = 0; //Boolean to check if user is logged in
    
    printf("Please enter your current email address: ");
    fgets(new_email, MAX, stdin); //Get new email from user
    new_email[strcspn(new_email, "\n")] = 0; //Remove newline character
    
    if (strcmp(old_email, new_email) == 0) {
        printf("Please enter your password: ");
        fgets(password, MAX, stdin); //Get password from user
        password[strcspn(password, "\n")] = 0; //Remove newline character
        
        if (strcmp(old_password, password) == 0) {
            isLoggedIn = 1; //User is logged in
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    }
    
    char new_password[MAX]; //New password input by user
    if (isLoggedIn) {
        printf("Please enter your new password: ");
        fgets(new_password, MAX, stdin); //Get new password from user
        new_password[strcspn(new_password, "\n")] = 0; //Remove newline character
        
        strcpy(old_email, new_email); //Update old email with new email
        strcpy(old_password, new_password); //Update old password with new password
    } else {
        printf("Incorrect email. Please try again.\n");
    }
    
    return 0;
}