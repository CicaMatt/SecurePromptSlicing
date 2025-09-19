#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User loggedInUser = {"user1", "oldemail@example.com", "password123"}; // Example logged-in user

int authenticatePassword(const char* inputPassword) {
    return strcmp(loggedInUser.password, inputPassword) == 0;
}

int verifyOldEmail(const char* oldEmail) {
    return strcmp(loggedInUser.email, oldEmail) == 0;
}

void changeUserEmail() {
    char oldEmail[100];
    char newPassword[50];
    char newEmail[100];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    if (!verifyOldEmail(oldEmail)) {
        printf("Invalid old email.\n");
        return;
    }

    printf("Confirm password: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0'; // Remove newline character

    if (!authenticatePassword(newPassword)) {
        printf("Incorrect confirm password.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    // Here you could add additional checks for the new email format or uniqueness
    strcpy(loggedInUser.email, newEmail); // Change user's email in the system
    printf("Email changed successfully to %s\n", loggedInUser.email);
}

int main() {
    changeUserEmail();
    return 0;
}