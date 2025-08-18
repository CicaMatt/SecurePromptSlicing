#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user123", "oldemail@example.com", "password123"};

void login(char *username, char *password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        exit(1);
    }
}

void changeEmail(char *newEmail, char *confirmPassword) {
    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect confirm password. Email not changed.\n");
        return;
    }

    // Simulate email existence check
    if (strlen(newEmail) == 0 || strcmp(newEmail, currentUser.email) == 0) {
        printf("New email must be different from the current one and non-empty.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to: %s\n", currentUser.email);
}

int main() {
    char username[50], password[50];
    char newEmail[100], confirmPassword[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    changeEmail(newEmail, confirmPassword);

    return 0;
}