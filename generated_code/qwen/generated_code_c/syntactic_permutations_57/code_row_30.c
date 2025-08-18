#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "securepassword"

int authenticate(const char* oldEmail, const char* confirmPassword) {
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, PASSWORD) == 0;
}

void changeEmail(char* newEmail) {
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (authenticate(oldEmail, confirmPassword)) {
        changeEmail(newEmail);
    } else {
        printf("Authentication failed. Please check your email and password.\n");
    }

    return 0;
}