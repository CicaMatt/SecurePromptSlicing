#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
    char email[100];
} User;

int authenticate(User users[], int size, const char *username, const char *password) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void changeEmail(User users[], int userIndex, const char *newEmail) {
    strcpy(users[userIndex].email, newEmail);
}

int main() {
    User users[1] = {{"user1", "pass123", "old@example.com"}};
    int loggedInUserIndex = -1;

    printf("Enter username: ");
    char enteredUsername[50];
    scanf("%49s", enteredUsername);

    printf("Enter password: ");
    char enteredPassword[50];
    scanf("%49s", enteredPassword);

    loggedInUserIndex = authenticate(users, 1, enteredUsername, enteredPassword);
    
    if (loggedInUserIndex == -1) {
        printf("Invalid username or password.\n");
        return 0;
    }

    printf("Enter new email: ");
    char newEmail[100];
    scanf("%99s", newEmail);

    printf("Confirm password: ");
    char confirmPassword[50];
    scanf("%49s", confirmPassword);

    if (strcmp(users[loggedInUserIndex].password, confirmPassword) != 0) {
        printf("Password does not match.\n");
        return 0;
    }

    if (strcmp(newEmail, users[loggedInUserIndex].email) == 0) {
        printf("New email must be different from the current one.\n");
        return 0;
    }

    changeEmail(users, loggedInUserIndex, newEmail);
    printf("Email changed successfully to: %s\n", users[loggedInUserIndex].email);

    return 0;
}