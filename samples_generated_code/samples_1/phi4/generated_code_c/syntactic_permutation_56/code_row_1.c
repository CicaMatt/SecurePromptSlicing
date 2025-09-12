#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20]; // Simple fixed length for demonstration purposes
} User;

// Function to simulate checking if the user is logged in
int isLoggedIn(User *user) {
    if (strcmp(user->email, "") == 0 || strcmp(user->password, "") == 0) {
        return 0;
    }
    return 1;
}

// Function to change the email of a logged-in user
void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the current one.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    fgets(confirmPassword, 20, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to: %s\n", user->email);
}

int main() {
    User currentUser = {"user@example.com", "password123"};

    if (isLoggedIn(&currentUser)) {
        changeEmail(&currentUser);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}