#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
    char email[100];
} User;

int authenticate(User *user, const char *inputUsername, const char *inputPassword) {
    return (strcmp(user->username, inputUsername) == 0 && strcmp(user->password, inputPassword) == 0);
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Old email does not match the current email.\n");
        return;
    }
    
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password. Cannot change email.\n");
        return;
    }
    
    strcpy(user->email, newEmail);
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    User currentUser = {"user123", "securePass123", "oldemail@example.com"};
    char inputUsername[50], inputPassword[50];
    char oldEmail[100], newPassword[50], newEmail[100], confirmPassword[50];

    printf("Login\n");
    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (!authenticate(&currentUser, inputUsername, inputPassword)) {
        printf("Authentication failed.\n");
        return 1;
    }

    printf("\nEnter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter new email: ");
    scanf("%99s", newEmail);
    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);
    
    return 0;
}