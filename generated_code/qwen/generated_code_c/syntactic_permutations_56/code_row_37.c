#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

void changeEmail(char oldEmail[], char newEmail[], const char* password, const char* storedPassword) {
    if (!authenticate(password, storedPassword)) {
        printf("Authentication failed. Incorrect password.\n");
        return;
    }
    
    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }
    
    strcpy(oldEmail, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    const char* storedPassword = "securepassword123";

    printf("Enter your old email: ");
    scanf("%s", newEmail); // Reusing newEmail for input to check if it matches oldEmail
    if (strcmp(newEmail, oldEmail) != 0) {
        printf("The entered email does not match the old email on record.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", password);

    changeEmail(oldEmail, newEmail, password, storedPassword);
    
    printf("Your current email is now: %s\n", oldEmail);
    
    return 0;
}