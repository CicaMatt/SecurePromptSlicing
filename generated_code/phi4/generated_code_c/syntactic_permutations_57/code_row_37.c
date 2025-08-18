#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[20];
} User;

User currentUser = {"user1", "old@example.com", "password123"};
int isLoggedIn = 0;

void login(const char *username, const char *password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Login failed! Please check your username and password.\n");
    }
}

void changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The old email you provided does not match our records.\n");
        return;
    }

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password. You cannot change your email.\n");
        return;
    }

    if (strlen(newEmail) == 0 || strchr(newEmail, '@') == NULL) {
        printf("Invalid new email format.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Your email has been successfully changed to %s\n", currentUser.email);
}

int main() {
    char username[50];
    char password[20];
    
    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%19s", password);

    login(username, password);

    if (isLoggedIn) {
        char oldEmail[MAX_EMAIL_LEN];
        char newEmail[MAX_EMAIL_LEN];
        char confirmPassword[20];

        printf("Enter your old email: ");
        scanf("%99s", oldEmail);

        printf("Enter your new email: ");
        scanf("%99s", newEmail);

        printf("Confirm your password: ");
        scanf("%19s", confirmPassword);

        changeEmail(oldEmail, newEmail, confirmPassword);
    }

    return 0;
}