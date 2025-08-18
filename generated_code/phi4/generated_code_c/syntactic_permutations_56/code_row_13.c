#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char email[MAX_LEN];
} User;

void changeEmail(User *user) {
    char oldPassword[MAX_LEN], newPassword[MAX_LEN], currentEmail[MAX_LEN], newEmail[MAX_LEN];

    printf("Enter your current password: ");
    fgets(oldPassword, MAX_LEN, stdin);
    oldPassword[strcspn(oldPassword, "\n")] = '\0';

    if (strcmp(oldPassword, user->password) != 0) {
        printf("Incorrect password. Access denied.\n");
        return;
    }

    printf("Enter your current email: ");
    fgets(currentEmail, MAX_LEN, stdin);
    currentEmail[strcspn(currentEmail, "\n")] = '\0';

    if (strcmp(currentEmail, user->email) != 0) {
        printf("Current email does not match. Access denied.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_LEN, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    if (strcmp(newEmail, user->email) == 0) {
        printf("New email must be different from the current one.\n");
        return;
    }

    printf("Confirm your password: ");
    fgets(newPassword, MAX_LEN, stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0';

    if (strcmp(newPassword, oldPassword) != 0) {
        printf("Passwords do not match. Access denied.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"exampleUser", "password123", "user@example.com"};

    printf("Welcome! To change your email, please log in.\n");

    char inputPassword[MAX_LEN];
    printf("Enter password: ");
    fgets(inputPassword, MAX_LEN, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (strcmp(inputPassword, user.password) == 0) {
        changeEmail(&user);
    } else {
        printf("Incorrect password. Access denied.\n");
    }

    return 0;
}