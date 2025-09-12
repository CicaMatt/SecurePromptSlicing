#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

// Function prototypes
int login(User users[], int size, char *username, char *password);
int changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword);

int main() {
    // Dummy user data for demonstration purposes
    User users[] = {
        {"user1", "pass123", "user1@example.com"},
        {"user2", "password", "user2@example.com"}
    };
    
    int numUsers = sizeof(users) / sizeof(User);
    char username[MAX_LENGTH], password[MAX_LENGTH];
    char oldEmail[MAX_LENGTH], newEmail[MAX_LENGTH], confirmPassword[MAX_LENGTH];

    printf("Login\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    int loggedInUserIndex = login(users, numUsers, username, password);

    if (loggedInUserIndex != -1) {
        User *currentUser = &users[loggedInUserIndex];

        printf("\nChange Email\n");
        printf("Old Email: ");
        scanf("%49s", oldEmail);
        printf("New Email: ");
        scanf("%49s", newEmail);
        printf("Confirm Password: ");
        scanf("%49s", confirmPassword);

        if (changeEmail(currentUser, oldEmail, newEmail, confirmPassword)) {
            printf("\nEmail changed successfully!\n");
        } else {
            printf("\nFailed to change email.\n");
        }
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}

int login(User users[], int size, char *username, char *password) {
    for (int i = 0; i < size; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

int changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match current email.\n");
        return 0;
    }

    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password entered.\n");
        return 0;
    }

    // Simple validation for demonstration: check new email is different and non-empty
    if (strcmp(newEmail, "") == 0 || strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old one and cannot be empty.\n");
        return 0;
    }

    strcpy(user->email, newEmail);
    return 1;
}