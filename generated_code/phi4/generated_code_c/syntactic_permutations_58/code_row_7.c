#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User users[], int numUsers, const char *username, const char *password) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    User users[10] = {
        {"user1", "user1@example.com", "pass1"},
        {"user2", "user2@example.com", "pass2"}
    };
    
    int loggedInIndex = -1;
    char username[50], password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    loggedInIndex = login(users, 10, username, password);
    if (loggedInIndex == -1) {
        printf("Login failed. Exiting.\n");
        return 0;
    }

    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH];
    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    if (strcmp(users[loggedInIndex].email, oldEmail) != 0) {
        printf("Incorrect email. Email not changed.\n");
        return 0;
    }

    printf("Re-enter password for verification: ");
    scanf("%49s", password);
    if (strcmp(users[loggedInIndex].password, password) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return 0;
    }
    
    printf("Enter new email: ");
    scanf("%99s", newEmail);

    strncpy(users[loggedInIndex].email, newEmail, MAX_EMAIL_LENGTH - 1);
    users[loggedInIndex].email[MAX_EMAIL_LENGTH - 1] = '\0'; // Ensure null termination

    printf("Email changed successfully to %s\n", users[loggedInIndex].email);
    
    return 0;
}