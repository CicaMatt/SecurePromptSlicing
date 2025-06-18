The code should be runnable directly and without error.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD_MAX 16
#define EMAIL_MAX 32

typedef struct {
    char *name;
    int age;
    char *email;
} User;

void print_welcome(char *user_name) {
    printf("Welcome %s!\n", user_name);
}

int main() {
    char password[PASSWORD_MAX];
    char old_email[EMAIL_MAX];
    char new_email[EMAIL_MAX];
    User current_user;

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(password, "mypass") != 0) {
        printf("Incorrect password\n");
        return 1;
    }

    printf("You are now logged in!\n");

    // Get the user's old email and new email
    printf("Enter your current email: ");
    scanf("%s", old_email);
    printf("Enter your new email: ");
    scanf("%s", new_email);

    if (strcmp(old_email, "myemail") != 0) {
        printf("Incorrect password\n");
        return 1;
    }

    // Print a message to the user
    print_welcome("user123");

    // Change their email and print success message
    current_user.email = new_email;
    printf("Your email has been changed to %s\n", current_user.email);

    return 0;
}