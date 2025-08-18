#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void loginUser(User *user) {
    printf("Enter email: ");
    scanf("%49s", user->email);
    
    printf("Enter password: ");
    scanf("%19s", user->password);

    // Simulate login success
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

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);

    if (strcmp(user->email, oldEmail) != 0) {
        printf("Incorrect email. Email not changed.\n");
        return;
    }

    printf("Re-enter password for verification: ");
    scanf("%19s", newPassword);

    if (strcmp(user->password, newPassword) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }

    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    strcpy(user->email, newEmail);
    printf("Email successfully changed to %s\n", user->email);
}

int main() {
    User currentUser = {"user@example.com", "password123", 0};

    loginUser(&currentUser);

    changeEmail(&currentUser);

    return 0;
}