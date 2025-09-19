#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int checkCredentials(const char *oldEmail, const char *confirmPassword) {
    // Dummy credentials for demonstration purposes
    const char *storedEmail = "user@example.com";
    const char *storedPassword = "securepassword";

    return strcmp(oldEmail, storedEmail) == 0 && strcmp(confirmPassword, storedPassword) == 0;
}

int updateEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!checkCredentials(oldEmail, confirmPassword)) {
        printf("Invalid old email or password.\n");
        return 0;
    }

    // Dummy update logic
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    if (updateEmail(oldEmail, newEmail, confirmPassword)) {
        printf("Email change successful.\n");
    } else {
        printf("Email change failed.\n");
    }

    return 0;
}