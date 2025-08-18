#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char password[50];
    char email[MAX_EMAIL_LENGTH];
} User;

User loggedInUser = {"user1", "password123", "oldemail@example.com"}; // Example logged-in user

int authenticate(const char* username, const char* password) {
    return strcmp(username, loggedInUser.username) == 0 && strcmp(password, loggedInUser.password) == 0;
}

void changeEmail() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[50];

    printf("Enter your old email: ");
    scanf("%s", old_email);

    if (strcmp(old_email, loggedInUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", new_email);

    if (strcmp(new_email, loggedInUser.email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    if (!authenticate(loggedInUser.username, confirm_password)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(loggedInUser.email, new_email);
    printf("Email changed successfully!\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if (!authenticate(username, password)) {
        printf("Authentication failed.\n");
        return 0;
    }

    changeEmail();

    return 0;
}