#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User loggedInUser = {"user1", "oldemail@example.com", "password123"};
User users[] = {loggedInUser};
int numUsers = 1;

void login() {
    char enteredEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[PASSWORD_LENGTH];

    printf("Enter email: ");
    scanf("%s", enteredEmail);
    printf("Enter password: ");
    scanf("%s", enteredPassword);

    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].email, enteredEmail) == 0 && strcmp(users[i].password, enteredPassword) == 0) {
            loggedInUser = users[i];
            printf("Login successful!\n");
            return;
        }
    }
    printf("Invalid email or password.\n");
}

int isDifferent(const char *oldEmail, const char *newEmail) {
    return strcmp(oldEmail, newEmail) != 0;
}

void changeEmail() {
    if (loggedInUser.username[0] == '\0') {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter old email: ");
    scanf("%s", oldEmail);
    if (strcmp(loggedInUser.email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Re-enter password: ");
    scanf("%s", newPassword);
    if (strcmp(loggedInUser.password, newPassword) != 0) {
        printf("Password incorrect.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (!isDifferent(loggedInUser.email, newEmail)) {
        printf("New email must be different from the old one.\n");
        return;
    }

    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].email, newEmail) == 0) {
            printf("This email is already in use by another account.\n");
            return;
        }
    }

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully to: %s\n", loggedInUser.email);
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                changeEmail();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}