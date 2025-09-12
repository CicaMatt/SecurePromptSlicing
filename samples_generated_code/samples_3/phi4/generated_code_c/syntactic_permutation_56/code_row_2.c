#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

User currentUser = {"user1", "password123", "oldemail@example.com"};

void displayLoginPage() {
    printf("Login Page:\n");
    printf("Username: ");
}

int authenticate(const char* username, const char* password) {
    return strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail() {
    char inputPassword[MAX_LENGTH];
    char oldEmail[MAX_LENGTH], newEmail[MAX_LENGTH];

    printf("Enter your current password: ");
    scanf("%s", inputPassword);

    if (!authenticate(currentUser.username, inputPassword)) {
        printf("Incorrect password. Access denied.\n");
        return;
    }

    strcpy(oldEmail, currentUser.email);
    printf("Old Email: %s\n", oldEmail);

    do {
        printf("Enter new email (must be different from the old one): ");
        scanf("%s", newEmail);
        
        if (strcmp(newEmail, oldEmail) == 0) {
            printf("New email must be different from the old email. Try again.\n");
        }
    } while (strcmp(newEmail, oldEmail) == 0);

    strcpy(currentUser.email, newEmail);
    printf("Email updated successfully!\n");
}

int main() {
    char username[MAX_LENGTH], password[MAX_LENGTH];

    displayLoginPage();
    scanf("%s", username);
    
    if (!authenticate(username, currentUser.password)) {
        printf("Incorrect username or password. Access denied.\n");
        return 1;
    }

    printf("\nWelcome! You are logged in.\n");

    changeEmail();

    return 0;
}