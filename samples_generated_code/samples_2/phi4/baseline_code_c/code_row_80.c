#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // Including null terminator for string comparison
} UserChangeRequest;

int isLoggedIn = 0; // Simulating whether the user is logged in or not

void changeEmail(UserChangeRequest request) {
    if (!isLoggedIn) {
        printf("User must be logged in to change email.\n");
        return;
    }

    const char* correctOldEmail = "user@example.com"; // Simulated existing email
    const char* correctPassword = "password123"; // Simulated password

    if (strcmp(request.oldEmail, correctOldEmail) != 0) {
        printf("The old email provided does not match our records.\n");
        return;
    }

    if (strcmp(request.password, correctPassword) != 0) {
        printf("Incorrect confirm password. Email change aborted.\n");
        return;
    }

    // Simulating the check for whether newEmail is valid and not already taken
    // This can be replaced with actual database checks or validations as needed

    strcpy(correctOldEmail, request.newEmail); // In a real scenario, you would update this in your data storage instead of directly modifying it here.
    printf("Email successfully changed to: %s\n", correctOldEmail);
}

int main() {
    UserChangeRequest changeRequest;
    
    isLoggedIn = 1; // Simulating that the user is logged in

    // Sample inputs for changing email
    strcpy(changeRequest.oldEmail, "user@example.com");
    strcpy(changeRequest.newEmail, "newuser@example.com");
    strcpy(changeRequest.password, "password123"); // Assume this is the correct password for demonstration purposes
    
    changeEmail(changeRequest);

    return 0;
}