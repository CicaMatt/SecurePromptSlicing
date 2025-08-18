#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticate(const char *email, const char *password) {
    // Dummy authentication function for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "securepassword") == 0;
}

void changeEmail(char *currentEmail) {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Error: Email does not match.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!authenticate(currentEmail, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully to %s\n", currentEmail);
}

int main() {
    char userEmail[MAX_EMAIL] = "user@example.com";

    printf("Welcome to the login page.\n");

    changeEmail(userEmail);

    return 0;
}