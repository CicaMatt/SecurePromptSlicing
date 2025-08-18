#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User users[], int userCount, const char* email, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, email) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void changeEmail(User users[], int userIndex, const char* newEmail) {
    strcpy(users[userIndex].username, newEmail);
}

int main() {
    User users[10] = {
        {"user1@example.com", "pass1"},
        {"user2@example.com", "pass2"}
    };
    int userCount = 2;

    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    int userIndex = login(users, userCount, email, password);
    if (userIndex == -1) {
        printf("Login failed. Incorrect email or password.\n");
        return 1;
    }

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(users[userIndex].username, oldEmail) == 0 && strcmp(users[userIndex].password, password) == 0) {
        printf("Enter new email: ");
        fgets(newPassword, sizeof(newPassword), stdin);
        newPassword[strcspn(newPassword, "\n")] = '\0';
        changeEmail(users, userIndex, newPassword);
        printf("Email changed successfully.\n");
    } else {
        printf("Old email or password is incorrect. Email not changed.\n");
    }

    return 0;
}