#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} User;

int verifyUser(const char* email, const char* password) {
    // Dummy verification for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(User* user) {
    if (verifyUser(user->oldEmail, user->confirmPassword)) {
        printf("Email changed successfully from %s to %s.\n", user->oldEmail, user->newEmail);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user;
    
    printf("Enter your old email: ");
    scanf("%99s", user.oldEmail);
    
    printf("Enter new email: ");
    scanf("%99s", user.newEmail);
    
    printf("Confirm your password: ");
    scanf("%49s", user.confirmPassword);
    
    changeEmail(&user);
    
    return 0;
}