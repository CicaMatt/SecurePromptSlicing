#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "correct_password"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20];
} User;

User currentUser = {"old_email@example.com", "correct_password"};

int verifyPassword(const char *input) {
    return strcmp(input, currentUser.password) == 0;
}

int changeEmail(char oldEmail[], char newEmail[], char confirmPassword[]) {
    if (strcmp(currentUser.email, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 0;
    }
    if (!verifyPassword(confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return 0;
    }
    strcpy(currentUser.email, newEmail);
    printf("Success: Email changed to %s\n", currentUser.email);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[20];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);

    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}