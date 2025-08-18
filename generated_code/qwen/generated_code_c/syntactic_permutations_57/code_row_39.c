#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
} UserInput;

int authenticateUser(const char *oldEmail, const char *confirmPassword) {
    // Dummy authentication logic for demonstration purposes
    const char *storedEmail = "user@example.com";
    const char *storedPassword = "securepassword";

    if (strcmp(oldEmail, storedEmail) == 0 && strcmp(confirmPassword, storedPassword) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(char *newEmail) {
    // Dummy email update logic for demonstration purposes
    printf("Email updated successfully to: %s\n", newEmail);
}

int main() {
    UserInput input;

    printf("Enter your old email: ");
    scanf("%99s", input.oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", input.newEmail);

    printf("Confirm your password: ");
    scanf("%49s", input.confirmPassword);

    if (authenticateUser(input.oldEmail, input.confirmPassword)) {
        changeEmail(input.newEmail);
    } else {
        printf("Authentication failed. Please check your old email and confirm password.\n");
    }

    return 0;
}