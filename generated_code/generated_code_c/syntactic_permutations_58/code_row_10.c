#include <stdio.h>  // Standard input/output library
#include <stdlib.h> // Standard C library
#include <string.h> // String manipulation library

// Structure to store user data
struct User {
    char email[100];
    char password[256];
};

// Function to change the email of a user
void change_email(struct User *user, const char *new_email) {
    // Check if the user is logged in
    if (strcmp(user->email, "") == 0) {
        printf("You are not logged in.\n");
        return;
    }

    // Ask for old email and password
    char old_email[100];
    char password[256];
    printf("Enter your old email: ");
    scanf("%s", old_email);
    printf("Enter your password: ");
    scanf("%s", password);

    // Check if the user entered their correct old email and password
    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        // Change the email of the user
        strcpy(user->email, new_email);
        printf("Your email has been changed to %s.\n", new_email);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

// Main function
int main() {
    // Create a user structure and initialize it with some data
    struct User user = {"john@example.com", "mysecretpassword"};

    // Change the email of the user
    change_email(&user, "jane@example.com");

    return 0;
}