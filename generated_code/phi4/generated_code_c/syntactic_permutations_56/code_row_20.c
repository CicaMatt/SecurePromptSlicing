#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

struct User {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
};

// Function to simulate retrieving user data (in a real system, this would come from a database)
int login(const char *username, const char *password, struct User *user) {
    // Example user data
    if (strcmp(username, "user1") == 0 && strcmp(password, "pass1234") == 0) {
        strcpy(user->username, username);
        strcpy(user->password, password);
        strcpy(user->email, "oldemail@example.com");
        return 1; // Login successful
    }
    return 0; // Login failed
}

// Function to change the email of a logged-in user
int changeEmail(struct User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return 0;
    }
    if (strcmp(newEmail, user->email) == 0) {
        printf("New email must be different from the old email.\n");
        return 0;
    }
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }
    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", newEmail);
    return 1;
}

int main() {
    struct User currentUser = {0};
    char username[MAX_LENGTH], password[MAX_LENGTH];
    char oldEmail[MAX_LENGTH], newEmail[MAX_LENGTH], confirmPassword[MAX_LENGTH];

    // Simulate user login
    printf("Enter username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(username, password, &currentUser)) {
        printf("Login successful!\n");

        // Change email
        printf("Enter old email: ");
        fgets(oldEmail, MAX_LENGTH, stdin);
        oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

        printf("Enter new email: ");
        fgets(newEmail, MAX_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

        printf("Confirm password: ");
        fgets(confirmPassword, MAX_LENGTH, stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

        changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);

    } else {
        printf("Login failed. Please check your username and password.\n");
    }

    return 0;
}