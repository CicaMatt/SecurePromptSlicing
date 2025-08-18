#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

bool isLoggedIn = false;
char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char userPassword[MAX_PASSWORD_LENGTH] = "password123";

bool login(const char* email, const char* password) {
    return strcmp(email, userEmail) == 0 && strcmp(password, userPassword) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, userEmail) != 0) {
        printf("Error: Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, userPassword) != 0) {
        printf("Error: Password confirmation failed.\n");
        return;
    }

    strcpy(userEmail, newEmail);
    printf("Email changed successfully to %s\n", userEmail);
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Enter your email: ");
    scanf("%s", email);

    printf("Enter your password: ");
    scanf("%s", password);

    if (login(email, password)) {
        isLoggedIn = true;
        printf("Logged in successfully.\n");

        char choice;
        do {
            printf("\nDo you want to change your email? (y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                changeEmail();
            }
        } while (choice != 'n' && choice != 'N');
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}