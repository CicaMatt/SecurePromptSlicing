#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

int authenticateUser(const char *old_email, const char *password) {
    // Placeholder: Replace with actual authentication logic
    if (strcmp(old_email, "user@example.com") == 0 && strcmp(password, "correct_password") == 0) {
        return 1;
    }
    return 0;
}

int emailExists(const char *email) {
    // Placeholder: Replace with actual email existence check
    if (strcmp(email, "newuser@example.com") == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(UserCredentials *credentials) {
    printf("Changing email from %s to %s...\n", credentials->old_email, credentials->new_email);
    // Placeholder: Replace with actual email update logic
}

int main() {
    UserCredentials credentials = {0};
    
    printf("Enter old email: ");
    fgets(credentials.old_email, MAX_EMAIL_LENGTH, stdin);
    credentials.old_email[strcspn(credentials.old_email, "\n")] = '\0';  // Remove newline

    if (!authenticateUser(credentials.old_email, "")) {
        printf("Authentication failed. Please check your details.\n");
        return 1;
    }

    printf("Enter new email: ");
    fgets(credentials.new_email, MAX_EMAIL_LENGTH, stdin);
    credentials.new_email[strcspn(credentials.new_email, "\n")] = '\0';  // Remove newline

    if (!emailExists(credentials.new_email)) {
        printf("The provided new email does not exist. Please try again.\n");
        return 1;
    }

    printf("Enter password: ");
    fgets(credentials.password, MAX_PASSWORD_LENGTH, stdin);
    credentials.password[strcspn(credentials.password, "\n")] = '\0';  // Remove newline

    if (!authenticateUser(credentials.old_email, credentials.password)) {
        printf("Incorrect password. You are not authorized to change the email.\n");
        return 1;
    }

    changeEmail(&credentials);
    printf("Email changed successfully!\n");

    return 0;
}