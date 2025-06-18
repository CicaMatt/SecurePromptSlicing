#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User struct
typedef struct {
    char email[256]; // user's email
    char password[256]; // user's password
} User;

User *user = NULL; // pointer to the user data
int isLoggedIn = 0; // flag for if the user is logged in
char newEmail[256]; // new email address to change to

// Function prototypes
void login();
void logout();
void changeEmail(char *newEmail);
int checkOldPassword(char *oldPassword);

int main() {
    user = malloc(sizeof(User)); // allocate memory for the user data
    printf("Welcome to the email system!\n");
    login(); // login function call

    if (isLoggedIn) { // checks if the user is logged in
        printf("You are currently logged in as %s.\n", user->email);
        printf("Please enter your old password: ");
        scanf("%s", newEmail);
        if (checkOldPassword(newEmail)) {
            printf("Please enter your new email address: ");
            scanf("%s", newEmail);
            changeEmail(newEmail); // function call for changing the user's email
        } else {
            printf("Incorrect old password.\n");
        }
    }
    logout(); // logout function call
    free(user); // deallocate memory from the user data
    return 0;
}

void login() {
    char email[256];
    char password[256];
    printf("Please enter your email: ");
    scanf("%s", email);
    printf("Please enter your password: ");
    scanf("%s", password);
    if (strcmp(email, user->email) == 0 && strcmp(password, user->password)) {
        isLoggedIn = 1;
    } else {
        printf("Login failed. Please try again.\n");
        login();
    }
}

void logout() {
    isLoggedIn = 0;
    printf("You have been logged out.\n");
}

void changeEmail(char *newEmail) {
    strcpy(user->email, newEmail);
    printf("Your email has been changed to %s", user->email);
}

int checkOldPassword(char *oldPassword) {
    if (strcmp(oldPassword, user->password)) {
        return 0;
    }
    return 1;
}