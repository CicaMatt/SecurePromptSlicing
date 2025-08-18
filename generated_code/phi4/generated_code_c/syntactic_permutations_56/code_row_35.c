#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWD_LEN 50

typedef struct {
    char username[MAX_EMAIL_LEN];
    char password[MAX_PASSWD_LEN];
} User;

void login(User *user) {
    char enteredUsername[MAX_EMAIL_LEN], enteredPassword[MAX_PASSWD_LEN];

    printf("Enter Username: ");
    fgets(enteredUsername, sizeof(enteredUsername), stdin);
    enteredUsername[strcspn(enteredUsername, "\n")] = 0; // Remove newline

    printf("Enter Password: ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = 0; // Remove newline

    if (strcmp(user->username, enteredUsername) == 0 &&
        strcmp(user->password, enteredPassword) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWD_LEN];

    printf("Enter Old Email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline

    if (strcmp(user->username, oldEmail) != 0) {
        printf("Old email does not match the current username.\n");
        exit(1);
    }

    printf("Enter New Email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old one.\n");
        exit(1);
    }

    printf("Enter Confirm Password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        exit(1);
    }

    strcpy(user->username, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"user@example.com", "securepass"};

    login(&user);

    changeEmail(&user);

    return 0;
}