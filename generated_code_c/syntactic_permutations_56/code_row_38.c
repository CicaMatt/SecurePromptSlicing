// This code is a simple login page that allows a user to change their email. The user must be logged in to change their email. The user must also enter their old email; new email and confirm password. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// define a struct for the user
typedef struct {
    char *email;
    char *password;
} User;

// function to read in the user's email and password from the command line
User read_user() {
    // create a new user
    User user = malloc(sizeof(User));

    // read in the email and password
    printf("Email: ");
    scanf("%s", user->email);
    printf("Password: ");
    scanf("%s", user->password);

    return user;
}

// function to change a user's email
void change_email(User *user) {
    // read in the old email and new email from the command line
    char old_email[100];
    printf("Old Email: ");
    scanf("%s", old_email);
    char new_email[100];
    printf("New Email: ");
    scanf("%s", new_email);

    // check that the user is logged in with the correct email and password
    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, "password") == 0) {
        // update the user's email to the new email
        free(user->email);
        user->email = malloc(sizeof(new_email));
        strcpy(user->email, new_email);
    } else {
        printf("Invalid email or password!\n");
        exit(1);
    }
}

// function to log out a user
void logout(User *user) {
    // free the user's email and password
    free(user->email);
    free(user->password);

    // free the user struct
    free(user);
}

int main() {
    // create a new user
    User user = read_user();

    // allow the user to change their email
    change_email(&user);

    // log out the user
    logout(&user);

    return 0;
}