#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int main() {
    User user;
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    char inputEmail[MAX_EMAIL];
    char oldEmail[MAX_EMAIL];
    char inputPassword[MAX_PASSWORD];

    printf("Enter your email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(inputPassword, MAX_PASSWORD, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = 0;

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, inputPassword) == 0) {
        printf("You are logged in.\nEnter your new email: ");
        fgets(inputEmail, MAX_EMAIL, stdin);
        inputEmail[strcspn(inputEmail, "\n")] = 0;

        strcpy(user.email, inputEmail);
        printf("Email changed successfully. Your new email is %s\n", user.email);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}