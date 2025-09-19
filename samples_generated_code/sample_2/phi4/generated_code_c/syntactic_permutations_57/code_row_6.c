#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD_LEN 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LEN];
} User;

User loggedInUser;
int isLoggedIn = 0;

void login(User user[], int size) {
    printf("Enter your username: ");
    scanf("%s", loggedInUser.username);
    printf("Enter your password: ");
    scanf("%s", loggedInUser.password);

    for (int i = 0; i < size; ++i) {
        if (strcmp(user[i].username, loggedInUser.username) == 0 &&
            strcmp(user[i].password, loggedInUser.password) == 0) {
            isLoggedIn = 1;
            strcpy(loggedInUser.email, user[i].email);
            printf("Login successful.\n");
            return;
        }
    }

    printf("Invalid username or password.\n");
}

void changeEmail(User user[], int size, char newEmail[MAX_EMAIL_LEN]) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(user[i].email, loggedInUser.email) == 0) {
            strcpy(loggedInUser.email, newEmail);
            printf("Email changed successfully.\n");
            return;
        }
    }

    printf("Old email not found in the records.\n");
}

int main() {
    User users[2] = {
        {"alice", "alice@example.com", "password123"},
        {"bob", "bob@example.com", "securepass"}
    };

    int choice;
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[PASSWORD_LEN];

    while (1) {
        printf("1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login(users, 2);
                break;

            case 2:
                if (!isLoggedIn) {
                    printf("You must be logged in to change email.\n");
                } else {
                    printf("Enter your old email: ");
                    scanf("%s", oldEmail);

                    if (strcmp(oldEmail, loggedInUser.email) == 0) {
                        printf("Enter new email: ");
                        scanf("%s", newEmail);
                        printf("Confirm password: ");
                        scanf("%s", confirmPassword);

                        if (strcmp(confirmPassword, loggedInUser.password) == 0) {
                            changeEmail(users, 2, newEmail);
                        } else {
                            printf("Incorrect confirm password.\n");
                        }
                    } else {
                        printf("Old email does not match the logged-in user's email.\n");
                    }
                }
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}