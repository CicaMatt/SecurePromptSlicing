#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20]; // Simple fixed length for demonstration purposes
} User;

User loggedInUser = {"existing@example.com", "password123"};

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    if (strcmp(user->email, oldEmail) != 0) {
        printf("Invalid old email.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect confirm password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    char inputPassword[20];

    printf("Enter your email: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (strcmp(loggedInUser.email, inputPassword) != 0) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    printf("Enter your password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (strcmp(loggedInUser.password, inputPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    changeEmail(&loggedInUser);

    return 0;
}