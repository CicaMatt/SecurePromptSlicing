#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20]; // Simple fixed length for demonstration; use secure storage in real applications.
} User;

User loggedInUser = {"user@example.com", "password123"}; // Example user, replace with actual authentication mechanism.

int authenticate(const char *email, const char *password) {
    return strcmp(loggedInUser.email, email) == 0 && strcmp(loggedInUser.password, password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    if (strcmp(loggedInUser.email, oldEmail) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    if (strlen(newEmail) == 0 || strcmp(oldEmail, newEmail) == 0) {
        printf("Invalid new email.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(loggedInUser.password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(loggedInUser.email, newEmail); // Change the email
    printf("Your email has been updated successfully!\n");
}

int main() {
    char loginEmail[MAX_EMAIL_LENGTH];
    char loginPassword[20];

    printf("Login to change your email:\n");

    printf("Enter your email: ");
    fgets(loginEmail, sizeof(loginEmail), stdin);
    loginEmail[strcspn(loginEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(loginPassword, sizeof(loginPassword), stdin);
    loginPassword[strcspn(loginPassword, "\n")] = '\0'; // Remove newline character

    if (authenticate(loginEmail, loginPassword)) {
        changeEmail();
    } else {
        printf("Authentication failed. Please check your email and password.\n");
    }

    return 0;
}