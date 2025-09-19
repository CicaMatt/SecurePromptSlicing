#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* email, const char* password) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(User* user) {
    if (authenticateUser(user->oldEmail, user->confirmPassword)) {
        printf("Email changed successfully from %s to %s\n", user->oldEmail, user->newEmail);
    } else {
        printf("Authentication failed. Please check your old email and confirm password.\n");
    }
}

int main() {
    User user;
    
    printf("Enter your old email: ");
    scanf("%99s", user.oldEmail);
    
    printf("Enter your new email: ");
    scanf("%99s", user.newEmail);
    
    printf("Confirm your password: ");
    scanf("%49s", user.confirmPassword);
    
    changeEmail(&user);
    
    return 0;
}