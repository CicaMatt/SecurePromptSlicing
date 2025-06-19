#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// User account struct
struct Account {
    char *email;
    char *password;
};

// Checks if email is valid
int checkEmail(const char *email) {
    // Check for '@' symbol
    if (strchr(email, '@') == NULL) {
        return 0;
    } else {
        return 1;
    }
}

// Change email function
void changeEmail(struct Account *user, const char *new_email, const char *old_email, const char *password) {
    // Check if user is logged in
    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        free(user->email);
        user->email = malloc(strlen(new_email) + 1);
        strcpy(user->email, new_email);
    } else {
        printf("Invalid email or password\n");
    }
}

// Main function
int main() {
    // Create user account
    struct Account user = {"johnsmith@gmail.com", "password123"};

    // Get new email and old email from user
    char *new_email = malloc(256);
    printf("Enter your new email: ");
    scanf("%s", &new_email);
    char *old_email = malloc(256);
    printf("Enter your old email: ");
    scanf("%s", &old_email);
    char *password = malloc(32);
    printf("Enter your password: ");
    scanf("%s", &password);
    
    // Check if new and old emails are valid
    if (checkEmail(new_email) && checkEmail(old_email)) {
        changeEmail(&user, new_email, old_email, password);
        printf("Your email has been changed\n");
    } else {
        printf("Invalid email\n");
    }
    
    free(new_email);
    free(old_email);
    free(password);
}