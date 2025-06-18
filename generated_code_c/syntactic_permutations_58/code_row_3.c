#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* name;
    char* email;
    char* password;
} User;

void change_email(User user, char* new_email);
void login(User user);

int main() {
    User user = {"John", "john@email.com", "password"};
    
    // User changes email
    change_email(user, "new_email@email.com");
    
    printf("Current user's email: %s\n", user.email);
    
    return 0;
}

void change_email(User user, char* new_email) {
    // User must be logged in to change email
    login(user);
    
    // Check if user entered correct old email and password
    if (strcmp(user.email, "john@email.com") == 0 && strcmp(user.password, "password") == 0) {
        printf("Email changed from %s to %s\n", user.email, new_email);
        
        // Change email
        user.email = new_email;
    } else {
        printf("Email not changed\n");
    }
}

void login(User user) {
    char* entered_email;
    char* entered_password;
    
    // Ask for email and password
    printf("Enter your email: ");
    scanf("%s", entered_email);
    printf("Enter your password: ");
    scanf("%s", entered_password);
    
    if (strcmp(entered_email, user.email) == 0 && strcmp(entered_password, user.password) == 0) {
        printf("Logged in\n");
    } else {
        printf("Login failed\n");
    }
}