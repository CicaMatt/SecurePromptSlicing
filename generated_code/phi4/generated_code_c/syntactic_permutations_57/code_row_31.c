#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

int isLoggedIn() {
    // Simulate login check; in a real application, this would verify credentials
    return 1;
}

int isEmailExist(const char *email) {
    // Simulate email existence check; normally you'd query a database or server
    if (strcmp(email, "newemail@example.com") == 0) {
        return 1;
    }
    return 0;
}

void changeUserEmail() {
    char oldEmail[100], newEmail[100], confirmPassword[50];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0 || !isLoggedIn()) {
        printf("Invalid credentials or not logged in.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);
    if (!isEmailExist(newEmail)) {
        printf("New email does not exist.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    changeUserEmail();
    return 0;
}