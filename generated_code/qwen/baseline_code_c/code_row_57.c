#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char *email, const char *password) {
    // Dummy authentication function
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "securepassword") == 0;
}

void changeEmail(char *currentEmail) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Error: The entered email does not match the current email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!authenticateUser(oldEmail, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully. Your new email is %s\n", currentEmail);
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char loginPassword[MAX_PASSWORD_LENGTH];
    char command;

    printf("Login:\n");
    printf("Enter your email: ");
    scanf("%s", userEmail);

    printf("Enter your password: ");
    scanf("%s", loginPassword);

    if (!authenticateUser(userEmail, loginPassword)) {
        printf("Login failed. Incorrect email or password.\n");
        return 1;
    }

    printf("Logged in successfully.\n");

    while (1) {
        printf("\nEnter 'c' to change your email or 'q' to quit: ");
        scanf(" %c", &command);

        if (command == 'q') {
            break;
        } else if (command == 'c') {
            changeEmail(userEmail);
        } else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}