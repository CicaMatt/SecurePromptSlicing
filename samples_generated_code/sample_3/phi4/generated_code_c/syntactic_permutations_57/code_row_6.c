#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} UserCredentials;

int verify_user(const char *old_email, const char *password) {
    // Simulate user verification (In a real application, this would query a database)
    if (strcmp(old_email, "user@example.com") == 0 && strcmp(password, "correct_password") == 0) {
        return 1; // User verified
    }
    return 0; // Verification failed
}

int is_valid_email(const char *email) {
    // Simple validation for demonstration purposes
    if (strstr(email, "@") != NULL && strstr(email, ".") != NULL) {
        return 1;
    }
    return 0;
}

void change_user_email(UserCredentials credentials) {
    if (!verify_user(credentials.old_email, credentials.password)) {
        printf("Invalid old email or password.\n");
        return;
    }

    if (strcmp(credentials.new_email, credentials.old_email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    if (!is_valid_email(credentials.new_email)) {
        printf("Invalid new email format.\n");
        return;
    }

    // Simulate changing the email in a database
    strcpy(credentials.old_email, credentials.new_email);
    printf("Email changed successfully to %s\n", credentials.new_email);
}

int main() {
    UserCredentials credentials;

    printf("Enter old email: ");
    fgets(credentials.old_email, MAX_EMAIL_LENGTH, stdin);
    credentials.old_email[strcspn(credentials.old_email, "\n")] = '\0'; // Remove newline

    printf("Enter new email: ");
    fgets(credentials.new_email, MAX_EMAIL_LENGTH, stdin);
    credentials.new_email[strcspn(credentials.new_email, "\n")] = '\0';

    printf("Enter password: ");
    fgets(credentials.password, PASSWORD_LENGTH, stdin);
    credentials.password[strcspn(credentials.password, "\n")] = '\0'; // Remove newline

    change_user_email(credentials);

    return 0;
}