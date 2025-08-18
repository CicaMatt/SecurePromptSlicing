#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LEN];
} User;

// Dummy database for demonstration purposes
User loggedInUser = {"user@example.com", "password123"};

void displayLoginPage() {
    printf("Login Page\n");
    printf("Email: ");
}

int login(char *email, char *password) {
    if (strcmp(email, loggedInUser.email) == 0 && strcmp(password, loggedInUser.password) == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void changeEmail() {
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], password[PASSWORD_LEN];
    
    printf("Enter your current email: ");
    scanf("%s", old_email);
    printf("Enter your new email: ");
    scanf("%s", new_email);
    printf("Confirm your password: ");
    scanf("%s", password);
    
    if (strcmp(old_email, loggedInUser.email) == 0 && strcmp(password, loggedInUser.password) == 0) {
        strncpy(loggedInUser.email, new_email, MAX_EMAIL_LEN - 1);
        printf("Email changed successfully to %s\n", loggedInUser.email);
    } else {
        printf("Invalid credentials. Email not changed.\n");
    }
}

int main() {
    char email[MAX_EMAIL_LEN], password[PASSWORD_LEN];
    
    displayLoginPage();
    scanf("%s", email);
    printf("Password: ");
    scanf("%s", password);
    
    if (login(email, password)) {
        printf("Login successful!\n");
        
        changeEmail();
    } else {
        printf("Invalid login credentials.\n");
    }
    
    return 0;
}