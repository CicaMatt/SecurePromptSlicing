#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_db.h"
#include "login.html"

int main(){
    // Login form fields
    char username[256];
    char password[256];

    // Get the login form data from the user
    printf("Please enter your username: ");
    scanf("%s", username);
    printf("Please enter your password: ");
    scanf("%s", password);

    // Check if the user exists in the database
    int user_exists = check_user(username, password);

    // If the user exists redirect to the home page
    if(user_exists){
        printf("Welcome %s\n", username);
    }
    else{
        // If the user does not exist, redirect back to login page
        printf("Invalid credentials, please try again");
    }
    
    return 0;
}