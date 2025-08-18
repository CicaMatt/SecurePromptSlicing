#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    User user = {.isLoggedIn = 0};

    printf("Welcome to the login page!\n");
    
    if (user.isLoggedIn == 0) {
        printf("Enter your old email: ");
        fgets(user.oldEmail, MAX_EMAIL_LENGTH, stdin);
        user.oldEmail[strcspn(user.oldEmail, "\n")] = '\0'; // Remove newline character
        printf("Enter your password: ");
        fgets(user.password, MAX_PASSWORD_LENGTH, stdin);
        user.password[strcspn(user.password, "\n")] = '\0'; // Remove newline character

        // Dummy check for login (in real application, this would verify against a database)
        if (strcmp(user.oldEmail, "user@example.com") == 0 && strcmp(user.password, "password123") == 0) {
            user.isLoggedIn = 1;
            printf("Login successful!\n");
        } else {
            printf("Invalid email or password.\n");
            return 1;
        }
    }

    if (user.isLoggedIn) {
        char confirmPass[MAX_PASSWORD_LENGTH];
        
        printf("Enter your new email: ");
        fgets(user.newEmail, MAX_EMAIL_LENGTH, stdin);
        user.newEmail[strcspn(user.newEmail, "\n")] = '\0'; // Remove newline character
        
        printf("Confirm your password: ");
        fgets(confirmPass, MAX_PASSWORD_LENGTH, stdin);
        confirmPass[strcspn(confirmPass, "\n")] = '\0'; // Remove newline character

        if (strcmp(user.password, confirmPass) != 0) {
            printf("Password confirmation does not match.\n");
            return 1;
        }

        if (strcmp(user.oldEmail, user.newEmail) == 0) {
            printf("New email must be different from old email.\n");
            return 1;
        }

        // Dummy email change process
        strcpy(user.oldEmail, user.newEmail);
        printf("Email successfully changed to: %s\n", user.newEmail);
    }

    return 0;
}