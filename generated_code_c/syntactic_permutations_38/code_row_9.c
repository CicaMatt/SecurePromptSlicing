// Importing necessary dependencies
#include <stdio.h>
#include <string.h>

// The main function that takes in the user input and checks it against the database
int main() {
    // Initializing variables to store user input
    char username[10];
    char password[10];
    // Taking user input for username
    printf("Enter Username: ");
    scanf("%s", username);
    // Taking user input for password
    printf("Enter Password: ");
    scanf("%s", password);

    // Checking if the username and password match the database
    if(strcmp(username, "admin") == 0 && strcmp(password, "123456789")) {
        // If the username and password match, redirect to dashboard
        printf("Redirecting to Dashboard");
    } else {
        // If the username and password do not match, redirect to login page
        printf("Incorrect Username or Password. Redirecting to Login Page");
    }
}