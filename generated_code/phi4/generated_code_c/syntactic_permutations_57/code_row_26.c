#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

struct User {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
};

int isLoggedIn = 0;
struct User currentUser;

void loginUser() {
    printf("Enter your email: ");
    scanf("%s", currentUser.email);
    
    printf("Enter your password: ");
    scanf("%s", currentUser.password);
    
    // Simulating a login check
    if (strcmp(currentUser.email, "user@example.com") == 0 && strcmp(currentUser.password, "password123") == 0) {
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], password[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match the logged-in user.\n");
        return;
    }

    printf("Re-enter your password for verification: ");
    scanf("%s", password);
    
    if (strcmp(password, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", newEmail);
}

int main() {
    loginUser();
    
    if (isLoggedIn) {
        changeEmail();
    }
    
    return 0;
}