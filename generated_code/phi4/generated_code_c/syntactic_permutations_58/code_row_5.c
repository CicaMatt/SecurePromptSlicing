#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

int is_logged_in() {
    return strcmp(currentUser.username, "") != 0;
}

int verify_credentials(char *oldEmail, char *enteredPassword) {
    return (strcmp(oldEmail, currentUser.email) == 0 && strcmp(enteredPassword, currentUser.password) == 0);
}

void change_email(char *newEmail) {
    if (is_logged_in()) {
        printf("Enter your old email: ");
        char oldEmail[MAX_EMAIL_LENGTH];
        fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
        oldEmail[strcspn(oldEmail, "\n")] = '\0';  // Remove newline

        printf("Confirm your password: ");
        char enteredPassword[MAX_PASSWORD_LENGTH];
        fgets(enteredPassword, MAX_PASSWORD_LENGTH, stdin);
        enteredPassword[strcspn(enteredPassword, "\n")] = '\0';  // Remove newline

        if (verify_credentials(oldEmail, enteredPassword)) {
            strcpy(currentUser.email, newEmail);
            printf("Email successfully changed to %s\n", currentUser.email);
        } else {
            printf("Incorrect old email or password. Email not changed.\n");
        }
    } else {
        printf("You must be logged in to change your email.\n");
    }
}

int main() {
    // Simulating user login
    strcpy(currentUser.username, "user1");

    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';  // Remove newline

    change_email(newEmail);

    return 0;
}