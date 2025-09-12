#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int checkCredentials(const char* enteredEmail, const char* enteredPassword) {
    // Dummy credentials for demonstration
    const char* correctEmail = "user@example.com";
    const char* correctPassword = "password123";

    return strcmp(enteredEmail, correctEmail) == 0 && strcmp(enteredPassword, correctPassword) == 0;
}

int main() {
    char currentEmail[MAX_EMAIL];
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your current email: ");
    fgets(currentEmail, MAX_EMAIL, stdin);
    currentEmail[strcspn(currentEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    if (!checkCredentials(currentEmail, password)) {
        printf("Incorrect email or password.\n");
        return 1;
    }

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("The entered old email does not match.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(newEmail, "") == 0) {
        printf("New email cannot be empty.\n");
        return 1;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(password, confirmPassword) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    // Update email logic here
    printf("Email updated successfully to %s\n", newEmail);

    return 0;
}