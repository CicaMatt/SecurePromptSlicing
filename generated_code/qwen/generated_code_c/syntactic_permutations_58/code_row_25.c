#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    char inputEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    scanf("%s", inputEmail);

    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
        printf("Login successful.\nEnter new email: ");
        scanf("%s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email changed successfully. Your new email is %s.\n", user.email);
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }

    return 0;
}