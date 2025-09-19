#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

int login(User users[], int size, char* username, char* password) {
    for (int i = 0; i < size; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void changeEmail(User* user, char* oldEmail, char* newPassword, char* newEmail) {
    if (user != NULL && strcmp(user->email, oldEmail) == 0 && strcmp(user->password, newPassword) == 0) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Check your credentials.\n");
    }
}

int main() {
    User users[1] = {{"user123", "old@example.com", "password"}};
    int userId;
    char username[50], password[50];
    char oldEmail[100], newPassword[50], newEmail[100];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    userId = login(users, 1, username, password);

    if (userId != -1) {
        printf("Login successful.\n");

        printf("Enter old email: ");
        scanf("%99s", oldEmail);
        printf("Confirm your password: ");
        scanf("%49s", newPassword);
        printf("Enter new email: ");
        scanf("%99s", newEmail);

        changeEmail(&users[userId], oldEmail, newPassword, newEmail);
    } else {
        printf("Login failed. Please check your credentials.\n");
    }

    return 0;
}