// Importing required libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining constants for success and failure of the program
#define SUCCESS 0
#define FAILURE 1

// Function to check if username and password is correct or not from the database
int checkLogin(char *username, char *password) {
    // Checking if username and password matches with the data in the database
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

// Main function to execute the program
int main() {
    // Declaring variables for username and password
    char username[256];
    char password[256];

    // Asking user to enter their username
    printf("Enter your username: ");
    scanf("%s", &username);

    // Asking user to enter their password
    printf("Enter your password: ");
    scanf("%s", &password);

    // Checking if the username and password is correct or not from the database
    int status = checkLogin(username, password);

    // Redirecting the user to dashboard if the login credentials are correct
    if (status == SUCCESS) {
        printf("Dashboard\n");
    } else {
        // Redirecting the user to the login page if the login credentials are incorrect
        printf("Login Page\n");
    }
    
    return 0;
}