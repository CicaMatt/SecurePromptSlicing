#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user, const char* username, const char* password) {
    // In a real application, this would check against stored credentials
    if (strcmp(username, "test@example.com") == 0 && strcmp(password, "password123") == 0) {
        strcpy(user->email, username);
        strcpy(user->password, password);
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

void changeEmail(User *user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(user->email, oldEmail) != 0 || strcmp(user->password, confirmPassword) != 0) {
        printf("Invalid old email or confirmation password.\n");
        return;
    }
    
    if (strlen(newEmail) == 0 || newEmail[0] == '\0') {
        printf("New email must be non-empty.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s.\n", user->email);
}

int main() {
    User currentUser = {"", "", 0};

    char username[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter email: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(&currentUser, username, password);

    if (currentUser.isLoggedIn) {
        char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];
        
        printf("Old email: ");
        scanf("%99s", oldEmail);
        printf("New email: ");
        scanf("%99s", newEmail);
        printf("Confirm password: ");
        scanf("%49s", confirmPassword);

        changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);
    }

    return 0;
}