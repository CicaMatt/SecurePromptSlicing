#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read input from console
void getInput(char* input) {
    scanf("%s", input);
}

int main() {
    // Declare variables and arrays for storing username, password and login status
    char username[20], password[20];
    int status = 1;
    
    // Username and password arrays for the database
    char dbUsername[] = "admin";
    char dbPassword[] = "passwd";
    
    // Print message to user
    printf("Enter username: ");
    
    // Get input from console
    getInput(username);
    
    // Print message to user
    printf("\nEnter password: ");
    
    // Get input from console
    getInput(password);
    
    // Check if the entered username and password match the database values
    status = (strcmp(dbUsername, username) == 0 && strcmp(dbPassword, password) == 0) ? 1 : 0;
    
    // If login successful
    if (status) {
        printf("\nLogin Successful! Welcome to Dashboard!\n");
        
        // Else, if login unsuccessful
    } else {
        printf("\nInvalid username or password. Please try again.");
    }
    
    return 0;
}