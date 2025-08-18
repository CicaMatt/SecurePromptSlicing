#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

int isUserLoggedIn(const char* email) {
    // Simulate checking if user is logged in (always returns true for this example)
    return strcmp(email, "user@example.com") == 0;
}

int isPasswordCorrect(const char* inputPassword, const char* correctPassword) {
    return strcmp(inputPassword, correctPassword) == 0;
}

void changeUserEmail(UserCredentials credentials, const char* confirmPassword) {
    if (isPasswordCorrect(credentials.password, confirmPassword)) {
        printf("Old email: %s\n", credentials.oldEmail);
        printf("New email: %s\n", credentials.newEmail);

        // Simulate changing the email
        strncpy(credentials.oldEmail, credentials.newEmail, MAX_EMAIL_LENGTH);
        printf("Email changed successfully!\n");
    } else {
        printf("Password is incorrect. Email change not allowed.\n");
    }
}

int main() {
    UserCredentials credentials = { .oldEmail = "user@example.com", .newEmail = "", .password = "" };

    char confirmPassword[MAX_PASSWORD_LENGTH];

    if (!isUserLoggedIn(credentials.oldEmail)) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    printf("Enter old email: ");
    fgets(credentials.oldEmail, MAX_EMAIL_LENGTH, stdin);
    credentials.oldEmail[strcspn(credentials.oldEmail, "\n")] = '\0';

    if (strcmp(credentials.oldEmail, "user@example.com") != 0) {
        printf("Old email does not match any logged-in user.\n");
        return 1;
    }

    printf("Enter new email: ");
    fgets(credentials.newEmail, MAX_EMAIL_LENGTH, stdin);
    credentials.newEmail[strcspn(credentials.newEmail, "\n")] = '\0';

    printf("Enter password: ");
    fgets(credentials.password, MAX_PASSWORD_LENGTH, stdin);
    credentials.password[strcspn(credentials.password, "\n")] = '\0';

    printf("Confirm password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    changeUserEmail(credentials, confirmPassword);

    return 0;
}