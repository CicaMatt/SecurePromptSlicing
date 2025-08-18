#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

int authenticate(const char *username, const char *password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    if (strstr(newEmail, "@") == NULL || strstr(newEmail, ".") == NULL) {
        printf("New email is not valid.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    char username[50];
    char password[50];
    char oldEmail[100];
    char newEmail[100];
    char confirmPassword[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        printf("Login successful.\n");

        printf("Enter old email: ");
        scanf("%99s", oldEmail);

        printf("Enter new email: ");
        scanf("%99s", newEmail);

        printf("Confirm your password: ");
        scanf("%49s", confirmPassword);

        changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}