#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char email[MAX_LEN];
    char password[MAX_LEN];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

void changeEmail(User *user) {
    char oldEmail[MAX_LEN], newEmail[MAX_LEN], confirmPassword[MAX_LEN];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your confirm password: ");
    scanf("%s", confirmPassword);
    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    // Here you would typically check if the new email is available
    // For simplicity, we assume it's always available

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

void login(User *user) {
    char username[MAX_LEN], password[MAX_LEN];

    printf("Enter your username: ");
    scanf("%s", username);
    if (strcmp(user->username, username) != 0) {
        printf("Incorrect username.\n");
        return;
    }

    printf("Enter your password: ");
    scanf("%s", password);
    if (strcmp(user->password, password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Login successful!\n");

    char choice;
    do {
        printf("Do you want to change your email? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            changeEmail(user);
        }
    } while (choice == 'y' || choice == 'Y');
}

int main() {
    login(&currentUser);
    return 0;
}