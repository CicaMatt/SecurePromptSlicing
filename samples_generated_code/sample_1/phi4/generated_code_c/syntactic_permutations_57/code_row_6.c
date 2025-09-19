#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user1", "old@example.com", "password123"};

int isLoggedIn(User user) {
    // Simple check to see if the user is logged in
    return strcmp(user.username, currentUser.username) == 0;
}

int verifyPassword(const char *inputPassword) {
    return strcmp(inputPassword, currentUser.password) == 0;
}

int validateEmailChange(const char *oldEmail, const char *newEmail) {
    // Check if the old email matches current user's email
    return strcmp(oldEmail, currentUser.email) == 0;
}

void changeUserEmail(User *user, const char *newEmail) {
    strcpy(user->email, newEmail);
}

int main() {
    User loggedInUser = {"user1", "old@example.com", "password123"};
    
    if (!isLoggedIn(loggedInUser)) {
        printf("Please log in first.\n");
        return 1;
    }
    
    char oldEmail[100];
    char newEmail[100];
    char confirmPassword[50];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (!validateEmailChange(oldEmail, loggedInUser.email)) {
        printf("The provided old email does not match the current account's email.\n");
    } else if (!verifyPassword(confirmPassword)) {
        printf("Incorrect password. Email change failed.\n");
    } else {
        changeUserEmail(&loggedInUser, newEmail);
        currentUser = loggedInUser;
        printf("Email successfully changed to %s\n", loggedInUser.email);
    }

    return 0;
}