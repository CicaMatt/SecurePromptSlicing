#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char* email, const char* password) {
    // Dummy authentication function
    // In a real application, this would check the provided credentials against a database
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int updateEmail(const char* oldEmail, const char* newEmail) {
    // Dummy email update function
    // In a real application, this would update the user's email in a database
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    
    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (!authenticateUser(oldEmail, confirmPassword)) {
        printf("Authentication failed. Please check your old email and password.\n");
        return 1;
    }

    updateEmail(oldEmail, newEmail);

    return 0;
}