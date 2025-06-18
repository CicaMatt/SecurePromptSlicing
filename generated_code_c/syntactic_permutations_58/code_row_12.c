#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if user is logged in
int isLoggedIn() {
    // Return 1 if user is logged in and 0 otherwise
}

// Function to update the email address for a user
void updateEmail(char* newEmail) {
    // Update the email address
}

// Main function to change the email
int main() {
    char oldEmail[50], password[16];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);
    
    // Check if user is logged in
    int loggedIn = isLoggedIn();
    if (loggedIn == 1) {
        updateEmail(newEmail);
    } else {
        printf("Invalid email or password");
    }
}