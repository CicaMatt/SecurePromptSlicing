#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
// Structure to store login credentials and email
typedef struct {
    char *email;
    char *password;
} LoginCredentials;

void changeEmail(LoginCredentials *login, char *newEmail) {
    // Check if user is logged in
    if (login->email == NULL || login->password == NULL) {
        printf("Please log in first.\n");
        return;
    }
 
    // Ask for old email and password
    printf("Enter your old email: ");
    char oldEmail[256];
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    char password[256];
    scanf("%s", password);
 
    // Check if user entered correct old email and password
    if (strcmp(oldEmail, login->email) == 0 && strcmp(password, login->password) == 0) {
        printf("You have successfully changed your email to %s.\n", newEmail);
        login->email = newEmail;
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    // Initialize login credentials and email
    LoginCredentials user = {"johnsmith@example.com", "password123"};
    char newEmail[256];
 
    // Ask for new email address
    printf("Enter your new email: ");
    scanf("%s", newEmail);
 
    changeEmail(&user, newEmail);
 
    return 0;
}