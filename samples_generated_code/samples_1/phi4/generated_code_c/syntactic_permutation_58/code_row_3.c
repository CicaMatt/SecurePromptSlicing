#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char currentEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your email: ");
    scanf("%s", user->currentEmail);
    
    printf("Enter your password: ");
    scanf("%s", user->password);
    
    // For simplicity, assume the entered credentials are valid
    user->isLoggedIn = 1;
    printf("Login successful!\n");
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }
    
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user->currentEmail) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (strcmp(newPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);
    
    strcpy(user->currentEmail, newEmail);
    printf("Email changed successfully to %s\n", user->currentEmail);
}

int main() {
    User user = { .isLoggedIn = 0 };
    
    login(&user);

    changeEmail(&user);

    return 0;
}