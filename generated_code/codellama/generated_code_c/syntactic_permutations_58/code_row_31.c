#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a structure to store user data
struct User {
    char* username;
    char* password;
    char* email;
};

// Create a function to change the user's email
void changeEmail(struct User *user, const char* new_email) {
    // Check if the user is logged in
    if (user != NULL && user->username != NULL && user->password != NULL) {
        // Check if the old email and password are correct
        if (strcmp(new_email, user->email) == 0 && strcmp(user->password, "password") == 0) {
            // Change the user's email
            user->email = new_email;
            printf("Email changed successfully!\n");
        } else {
            printf("Invalid old email or password\n");
        }
    } else {
        printf("User not logged in\n");
    }
}

int main() {
    // Create a user structure and set the username, password, and email
    struct User user = {"John", "password", "john@example.com"};
    
    // Change the user's email to "jane@example.com"
    changeEmail(&user, "jane@example.com");
    
    return 0;
}