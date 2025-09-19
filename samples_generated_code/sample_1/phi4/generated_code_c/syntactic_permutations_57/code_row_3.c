#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

int authenticate(const char *oldEmail, const char *password) {
    // Mock authentication: Assume correct credentials are "user@example.com" and "password123"
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int isEmailValid(const char *email) {
    // Simple validation check for email format
    return strstr(email, "@") != NULL && strstr(email, ".") != NULL;
}

void changeEmail(UserCredentials credentials) {
    if (authenticate(credentials.oldEmail, credentials.password)) {
        if (isEmailValid(credentials.newEmail)) {
            printf("Email changed successfully from %s to %s\n", credentials.oldEmail, credentials.newEmail);
        } else {
            printf("Invalid new email format.\n");
        }
    } else {
        printf("Authentication failed. Incorrect old email or password.\n");
    }
}

int main() {
    UserCredentials credentials;
    
    printf("Enter your old email: ");
    fgets(credentials.oldEmail, MAX_EMAIL_LENGTH, stdin);
    credentials.oldEmail[strcspn(credentials.oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter new email: ");
    fgets(credentials.newEmail, MAX_EMAIL_LENGTH, stdin);
    credentials.newEmail[strcspn(credentials.newEmail, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(credentials.password, MAX_PASSWORD_LENGTH, stdin);
    credentials.password[strcspn(credentials.password, "\n")] = '\0';
    
    changeEmail(credentials);

    return 0;
}