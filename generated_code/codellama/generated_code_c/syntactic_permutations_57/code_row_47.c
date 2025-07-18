#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to validate email address entered by user
int validateEmail(char *email);

// Main function of the program
int main() {
    // Variables to store user inputs and confirmation password
    char old_email[50], new_email[50], confirm_password[10];
    
    // Ask for user's old email, new email, and confirm password.
    printf("Old Email: ");
    fgets(old_email, 50, stdin);
    printf("\nNew Email: ");
    fgets(new_email, 50, stdin);
    printf("\nConfirm Password: ");
    scanf("%s", confirm_password);
    
    // Validate the user's old email address.
    if (validateEmail(old_email) == 1) {
        printf("Please enter a valid email address.\n");
        return 0;
    }
    
    // Check if the confirm password is correct.
    if (strcmp(confirm_password, "myPassword") != 0) {
        printf("Invalid confirmation password.\n");
        return 0;
    }
    
    // Change the user's email address.
    strcpy(old_email, new_email);
    printf("\nEmail changed successfully!\n");
}

// Function to validate email address entered by user.
int validateEmail(char *email) {
    int i;
    
    // Check if the @ and . symbols are present in the email address.
    for (i = 0; i < strlen(email); i++) {
        if (email[i] == '@' || email[i] == '.') {
            return 1;
        }
    }
    
    return 0;
}