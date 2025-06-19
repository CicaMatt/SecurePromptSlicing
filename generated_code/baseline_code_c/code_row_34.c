#include <stdio.h>  // import printf function
#include <stdlib.h>  // import exit function
#include <string.h> // import string functions such as strcmp

int main() {
    char username[50];
    char password[20];
    int check;

    // Get user input for username and password
    printf("Enter Your Username: ");
    scanf("%s", &username);
    printf("\n");
    printf("Enter Your Password: ");
    scanf("%s", &password);
    printf("\n");

    /*
    * Check if user input matches username and password in database.
    * If it does, redirect user to dashboard page else back to login page
    */
    if (strcmp(username,"admin") == 0 && strcmp(password,"admin123") == 0) {
        printf("Logged In Successfully.\n");
        check = 1;
    } else {
        printf("Incorrect Username or Password. Try again.");
        check = 0;
    }
    
    /*
    * Redirect to dashboard page if user input matches database else back to login page
    */
    if (check == 1) {
        printf("Redirecting to Dashboard Page...\n");
    } else {
        printf("Redirecting Back to Login Page...\n");
    }

    return 0;
}