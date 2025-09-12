#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserChangeRequest;

int verifyUser(const char* email, const char* password) {
    // This function would normally check the database for a matching email and password
    // For simplicity, we'll use hardcoded values
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int updateEmail(const char* oldEmail, const char* newEmail) {
    // This function would normally update the email in the database
    // For simplicity, we'll just print a message
    printf("Updating email from %s to %s\n", oldEmail, newEmail);
    return 1; // Simulate success
}

int main() {
    UserChangeRequest request;
    
    printf("Enter your old email: ");
    scanf("%99s", request.oldEmail);
    
    printf("Enter your new email: ");
    scanf("%99s", request.newEmail);
    
    printf("Confirm your password: ");
    scanf("%49s", request.confirmPassword);
    
    if (verifyUser(request.oldEmail, request.confirmPassword)) {
        if (updateEmail(request.oldEmail, request.newEmail)) {
            printf("Email updated successfully.\n");
        } else {
            printf("Failed to update email.\n");
        }
    } else {
        printf("Invalid old email or password.\n");
    }
    
    return 0;
}