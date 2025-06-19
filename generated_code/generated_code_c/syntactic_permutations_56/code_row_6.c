// include libraries
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// define constants
#define MAX_EMAIL_LEN 50
#define PASSWORD_LEN 16

// define structs
typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LEN];
} User;

// function prototypes
bool isEmailValid(char* email);
bool isPasswordValid(char* password);
void changeEmail(User* user, char* newEmail, char* confirmPassword);

int main() {
    // create and initialize variables
    User user = {"johndoe@email.com", "123456"};
    char newEmail[MAX_EMAIL_LEN] = "";
    char confirmPassword[PASSWORD_LEN] = "";
    bool emailChanged = false;

    // prompt user for input
    printf("Enter your old email: ");
    fgets(user.email, MAX_EMAIL_LEN, stdin);
    strtok(user.email, "\n"); // remove newline from email string

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LEN, stdin);
    strtok(newEmail, "\n"); // remove newline from email string

    printf("Confirm password: ");
    fgets(confirmPassword, PASSWORD_LEN, stdin);
    strtok(confirmPassword, "\n"); // remove newline from password string

    // validate user input
    if (!isEmailValid(newEmail)) {
        printf("Invalid email! Please enter a valid email.\n");
    } else if (!isPasswordValid(confirmPassword)) {
        printf("Invalid password! Please enter a valid password.\n");
    } else if (strcmp(user.password, confirmPassword) != 0) {
        printf("Wrong password! Please enter the correct password.\n");
    } else if (strcmp(user.email, newEmail) == 0) {
        printf("New email cannot be the same as old email!\n");
    } else {
        changeEmail(&user, newEmail, confirmPassword);
        emailChanged = true;
    }

    // print result
    if (emailChanged) {
        printf("%s's email has been changed to %s.\n", user.name, newEmail);
    } else {
        printf("Email could not be changed. Please try again.\n");
    }

    return 0;
}

bool isEmailValid(char* email) {
    // TODO: implement email validation logic here
    return true;
}

bool isPasswordValid(char* password) {
    // TODO: implement password validation logic here
    return true;
}

void changeEmail(User* user, char* newEmail, char* confirmPassword) {
    strcpy(user->email, newEmail);
    strcpy(user->password, confirmPassword);
}