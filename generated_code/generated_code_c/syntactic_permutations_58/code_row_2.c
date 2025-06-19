#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
    char* email;
} User;

void changeEmail(User user, char* newEmail) {
    // validate email
    if (isValidEmail(newEmail)) {
        strcpy(user.email, newEmail);
    } else {
        printf("Invalid email: %s\n", newEmail);
    }
}

int isValidEmail(char* email) {
    // use a regex here
    return 1;
}

int main() {
    User user = {"john", "password", "john@example.com"};
    char newEmail[50];

    printf("Please enter your old email: ");
    scanf("%s", user.email);
    printf("Please enter your password: ");
    scanf("%s", user.password);
    printf("Please enter your new email: ");
    scanf("%s", newEmail);

    if (user.username == "john" && user.password == "password") {
        changeEmail(user, newEmail);
        printf("Your email has been changed to %s\n", user.email);
    } else {
        printf("Invalid username and/or password\n");
    }

    return 0;
}