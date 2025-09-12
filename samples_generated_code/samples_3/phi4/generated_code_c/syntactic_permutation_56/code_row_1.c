#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
    char email[100];
} User;

User currentUser = {"user123", "password123", "user@example.com"};

int authenticate(char *username, char *password) {
    return strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}

int changeEmail(char *newEmail, char *confirmPassword) {
    if (strcmp(currentUser.email, newEmail) == 0) {
        printf("New email must be different from the current one.\n");
        return 0;
    }
    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }
    strcpy(currentUser.email, newEmail);
    printf("Email successfully updated to %s\n", currentUser.email);
    return 1;
}

int main() {
    char username[50], password[50];
    char newEmail[100], confirmPassword[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (!authenticate(username, password)) {
        printf("Authentication failed.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    changeEmail(newEmail, confirmPassword);

    return 0;
}