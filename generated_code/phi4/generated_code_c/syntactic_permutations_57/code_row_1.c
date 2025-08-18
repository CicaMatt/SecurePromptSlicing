#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[20];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};
int isLoggedIn = 0;

void displayLoginPage() {
    printf("Welcome to the Login Page\n");
}

int login(char *username, char *password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        isLoggedIn = 1;
        return 1;
    }
    return 0;
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[20];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The provided email does not match our records.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm password: ");
    fgets(confirmPassword, 20, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect confirm password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char username[50], password[20];

    displayLoginPage();

    printf("Enter username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, 20, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (login(username, password)) {
        printf("Login successful!\n");
        changeEmail();
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}