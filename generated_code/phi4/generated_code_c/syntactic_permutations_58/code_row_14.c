#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

int login(User users[], int numUsers, const char* username, const char* password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void changeEmail(User users[], int loggedInUserIndex, const char* oldEmail, const char* newPassword, const char* newEmail) {
    if (strcmp(users[loggedInUserIndex].email, oldEmail) == 0 && strcmp(users[loggedInUserIndex].password, newPassword) == 0) {
        strcpy(users[loggedInUserIndex].email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User users[] = {
        {"user1", "oldemail1@example.com", "password1"},
        {"user2", "oldemail2@example.com", "password2"}
    };
    int numUsers = sizeof(users) / sizeof(users[0]);
    
    char username[50], password[MAX_PASS_LEN];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    int loggedInUserIndex = login(users, numUsers, username, password);
    if (loggedInUserIndex == -1) {
        printf("Login failed. Incorrect username or password.\n");
        return 0;
    }

    char oldEmail[MAX_EMAIL_LEN], newPassword[MAX_PASS_LEN], newEmail[MAX_EMAIL_LEN];
    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", newPassword);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    changeEmail(users, loggedInUserIndex, oldEmail, newPassword, newEmail);

    return 0;
}