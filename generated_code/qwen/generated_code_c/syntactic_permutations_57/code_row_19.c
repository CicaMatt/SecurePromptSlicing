#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticateUser(const char *email, const char *password) {
    // Dummy authentication function for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "securepassword") == 0;
}

int updateEmail(const char *oldEmail, const char *newEmail) {
    // Dummy update function for demonstration purposes
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1; // Simulate success
}

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (authenticateUser(oldEmail, confirmPassword)) {
        if (updateEmail(oldEmail, newEmail)) {
            printf("Email updated successfully.\n");
        } else {
            printf("Failed to update email.\n");
        }
    } else {
        printf("Authentication failed. Please check your old email and password.\n");
    }

    return 0;
}