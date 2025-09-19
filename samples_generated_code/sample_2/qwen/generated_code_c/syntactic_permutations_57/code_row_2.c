#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticate(const char* oldEmail, const char* confirmPassword) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

void changeEmail(char* newEmail) {
    printf("Email changed to: %s\n", newEmail);
}

int main() {
    char oldEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your password to confirm: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (authenticate(oldEmail, confirmPassword)) {
        printf("Enter new email: ");
        fgets(newEmail, MAX_EMAIL, stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;

        changeEmail(newEmail);
    } else {
        printf("Authentication failed. Please check your old email and password.\n");
    }

    return 0;
}