#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct User {
    char old_email[MAX_EMAIL_LENGTH];
    char password[20]; // Simple fixed length for demonstration
} User;

User currentUser = {"user@example.com", "password123"};

void displayLoginPage() {
    printf("Login Page\n");
    printf("Email: %s\n", currentUser.old_email);
}

int login(char *input_email, char *input_password) {
    return (strcmp(input_email, currentUser.old_email) == 0 && strcmp(input_password, currentUser.password) == 0);
}

void changeEmail() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[20];

    printf("Enter your current email: ");
    scanf("%s", old_email);

    if (strcmp(old_email, currentUser.old_email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your password to verify: ");
    scanf("%s", password);
    
    if (strcmp(password, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }
    
    printf("Enter new email: ");
    scanf("%s", new_email);

    strcpy(currentUser.old_email, new_email);
    printf("Email changed successfully to %s\n", new_email);
}

int main() {
    char input_email[MAX_EMAIL_LENGTH];
    char input_password[20];

    displayLoginPage();
    
    printf("Login to change email.\n");
    printf("Enter email: ");
    scanf("%s", input_email);

    printf("Enter password: ");
    scanf("%s", input_password);
    
    if (login(input_email, input_password)) {
        changeEmail();
    } else {
        printf("Failed login. Access denied.\n");
    }

    return 0;
}