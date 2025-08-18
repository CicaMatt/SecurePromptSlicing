#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

void login() {
    char inputUsername[50], inputPassword[50];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);

    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, currentUser.username) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        printf("Login successful!\n");
        changeEmail();
    } else {
        printf("Invalid username or password.\n");
    }
}

void changeEmail() {
    char oldEmail[100], newEmail[100], confirmPassword[50];
    char inputPassword[50];

    printf("Enter Old Email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter Password to confirm change: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter New Email: ");
    scanf("%99s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm Password: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect confirmation password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email updated successfully!\n");
}

int main() {
    login();
    return 0;
}