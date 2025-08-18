#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user1", "old@example.com", "password123"};

void login() {
    printf("Please log in:\n");
    printf("Username: ");
    scanf("%s", currentUser.username);
    printf("Password: ");
    scanf("%s", currentUser.password);

    if (strcmp(currentUser.username, "user1") == 0 && strcmp(currentUser.password, "password123") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect username or password. Try again.\n");
        login();
    }
}

void changeEmail() {
    char newEmail[100];
    char confirmPassword[50];

    printf("\nEnter your current email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentUser.email) != 0) {
        printf("Incorrect email. Try again.\n");
        changeEmail();
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm password to verify ownership: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect confirm password. Try again.\n");
        changeEmail();
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    login();
    changeEmail();

    printf("\nYour updated email is: %s\n", currentUser.email);

    return 0;
}