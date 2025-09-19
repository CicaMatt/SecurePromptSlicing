#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char password[50];
    char email[MAX_EMAIL_LENGTH];
} User;

User loggedInUser;
int isLoggedIn = 0;

void login(User users[], int userCount) {
    char inputUsername[50], inputPassword[50];

    printf("Enter Username: ");
    scanf("%s", inputUsername);
    printf("Enter Password: ");
    scanf("%s", inputPassword);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, inputUsername) == 0 && strcmp(users[i].password, inputPassword) == 0) {
            loggedInUser = users[i];
            isLoggedIn = 1;
            printf("Login successful!\n");
            return;
        }
    }

    printf("Invalid username or password.\n");
}

void changeEmail(User users[], int userCount) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH], newPassword[50], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter Old Email: ");
    scanf("%s", oldEmail);
    printf("Confirm Password: ");
    scanf("%s", newPassword);

    if (strcmp(loggedInUser.email, oldEmail) == 0 && strcmp(loggedInUser.password, newPassword) == 0) {
        printf("Enter New Email: ");
        scanf("%s", newEmail);
        strcpy(loggedInUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Old email or password is incorrect. Email not changed.\n");
    }
}

int main() {
    User users[] = {
        {"user1", "pass1", "user1@example.com"},
        {"user2", "pass2", "user2@example.com"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            login(users, userCount);
        } else if (choice == 2) {
            changeEmail(users, userCount);
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}