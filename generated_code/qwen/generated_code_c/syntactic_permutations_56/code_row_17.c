#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

int authenticateUser(const UserCredentials *user) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(user->password, "correctPassword") == 0;
}

int validateEmailChange(const char *oldEmail, const char *newEmail) {
    return strcmp(oldEmail, newEmail) != 0;
}

void changeEmail() {
    UserCredentials user;
    
    printf("Enter your old email: ");
    scanf("%s", user.oldEmail);
    
    printf("Enter your password: ");
    scanf("%s", user.password);
    
    if (!authenticateUser(&user)) {
        printf("Authentication failed. Please try again.\n");
        return;
    }
    
    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    
    if (!validateEmailChange(user.oldEmail, newEmail)) {
        printf("New email must be different from old email.\n");
        return;
    }
    
    printf("Email changed successfully to %s\n", newEmail);
}

int main() {
    changeEmail();
    return 0;
}