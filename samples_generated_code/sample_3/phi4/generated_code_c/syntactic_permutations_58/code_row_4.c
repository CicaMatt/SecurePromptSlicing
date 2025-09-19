#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

void login() {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", inputEmail);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(currentUser.email, inputEmail) == 0 && strcmp(currentUser.password, inputPassword) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect email or password. Access denied.\n");
        exit(0);
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);

    if (strcmp(currentUser.email, oldEmail) == 0 && strcmp(currentUser.password, confirmPassword) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect current email or password. Email not changed.\n");
    }
}

int main() {
    login();
    changeEmail();

    printf("Current email: %s\n", currentUser.email);

    return 0;
}