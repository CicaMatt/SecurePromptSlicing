#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

User current_user = {"user1", "password123", "oldemail@example.com"};

int login(const char *username, const char *password) {
    if (strcmp(username, current_user.username) == 0 && strcmp(password, current_user.password) == 0) {
        return 1;
    }
    return 0;
}

int change_email(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(current_user.email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return 0;
    }

    if (strcmp(confirmPassword, current_user.password) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }

    if (strcmp(newEmail, current_user.email) == 0) {
        printf("New email must be different from the old email.\n");
        return 0;
    }

    strncpy(current_user.email, newEmail, MAX_LENGTH);
    printf("Email updated successfully!\n");
    return 1;
}

int main() {
    char username[MAX_LENGTH], password[MAX_LENGTH];
    char oldEmail[MAX_LENGTH], newEmail[MAX_LENGTH], confirmPassword[MAX_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    if (!login(username, password)) {
        printf("Login failed. Please check your credentials.\n");
        return 1;
    }

    printf("Enter Old Email: ");
    scanf("%s", oldEmail);

    printf("Enter New Email: ");
    scanf("%s", newEmail);

    printf("Confirm Password: ");
    scanf("%s", confirmPassword);

    if (!change_email(oldEmail, newEmail, confirmPassword)) {
        return 1;
    }

    return 0;
}