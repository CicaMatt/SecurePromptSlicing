#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char confirmed_password[MAX_PASSWORD_LENGTH];
} UserCredentials;

int validateEmail(const char *email) {
    if (strlen(email) == 0 || strstr(email, "@") == NULL || strstr(email, ".") == NULL)
        return 0;
    return 1;
}

int main() {
    UserCredentials credentials;
    char stored_password[MAX_PASSWORD_LENGTH] = "user_password"; // This should be securely hashed and managed in a real system
    int emailChanged = 0;

    printf("Enter old email: ");
    scanf("%s", credentials.old_email);

    if (!validateEmail(credentials.old_email)) {
        printf("Invalid email format.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", credentials.new_email);

    if (!validateEmail(credentials.new_email)) {
        printf("Invalid email format.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%s", credentials.password);

    printf("Confirm password: ");
    scanf("%s", credentials.confirmed_password);

    if (strcmp(credentials.password, credentials.confirmed_password) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    // Simulate verifying the old email and password
    if (strcmp(credentials.old_email, "existing_user@example.com") == 0 &&
        strcmp(credentials.password, stored_password) == 0) {
        
        printf("Email changed successfully from %s to %s.\n", credentials.old_email, credentials.new_email);
        emailChanged = 1;
    } else {
        printf("Invalid old email or password.\n");
    }

    return emailChanged ? 0 : 1;
}