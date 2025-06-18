// The following C code implements a simple login system. 
// It takes in a username and password from the user and checks it against the database.
// If the username and password are correct, the user is granted access.
// Otherwise, the user is redirected to the login page.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[20];
    char password[20];
    
    // Ask for the username and password from the user.
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your password: ");
    scanf("%s", &password);
    
    // Check if the username and password are correct.
    // If they are, grant access to the user.
    // Otherwise, redirect them to the login page.
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("Welcome! You have been granted access.\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        main();
    }
    
    return 0;
}