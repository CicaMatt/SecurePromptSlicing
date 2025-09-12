#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
} UserInput;

int validateCredentials(const char *email, const char *password) {
    // Dummy validation logic for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "securepassword123") == 0;
}

int updateEmail(const char *oldEmail, const char *newEmail) {
    // Dummy email update logic for demonstration purposes
    if (strcmp(oldEmail, "user@example.com") != 0) {
        return 0; // Old email does not match
    }
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1;
}

int main() {
    UserInput userInput;

    printf("Enter your old email: ");
    scanf("%99s", userInput.oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", userInput.newEmail);

    printf("Confirm your password: ");
    scanf("%49s", userInput.confirmPassword);

    if (!validateCredentials(userInput.oldEmail, userInput.confirmPassword)) {
        printf("Invalid credentials. Please try again.\n");
        return 1;
    }

    if (updateEmail(userInput.oldEmail, userInput.newEmail)) {
        printf("Your email has been successfully updated.\n");
    } else {
        printf("Failed to update email. Old email does not match.\n");
    }

    return 0;
}