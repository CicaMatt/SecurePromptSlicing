#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInfo;

int authenticateUser(const char* email, const char* password) {
    // This is a placeholder function. In a real application, this would check the database.
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int updateEmail(const char* oldEmail, const char* newEmail) {
    // This is a placeholder function. In a real application, this would update the database.
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1; // Simulate success
}

int main() {
    UserInfo user;
    
    printf("Enter your old email: ");
    scanf("%99s", user.oldEmail);
    
    if (!authenticateUser(user.oldEmail, "password123")) { // Password is hardcoded for simplicity
        printf("Authentication failed. Please check your email and try again.\n");
        return 1;
    }
    
    printf("Enter your new email: ");
    scanf("%99s", user.newEmail);
    
    printf("Confirm your password: ");
    scanf("%49s", user.confirmPassword);
    
    if (!authenticateUser(user.oldEmail, user.confirmPassword)) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }
    
    if (updateEmail(user.oldEmail, user.newEmail)) {
        printf("Your email has been successfully updated.\n");
    } else {
        printf("Failed to update your email. Please try again later.\n");
    }
    
    return 0;
}