#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char email[MAX_LEN];
    char password[MAX_LEN];
} User;

void login(User *user) {
    char inputEmail[MAX_LEN], inputPassword[MAX_LEN];
    
    printf("Enter your old email: ");
    fgets(inputEmail, sizeof(inputEmail), stdin);
    inputEmail[strcspn(inputEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(user->email, inputEmail) == 0 && strcmp(user->password, inputPassword) == 0) {
        printf("Login successful!\n");
        
        char newEmail[MAX_LEN];
        printf("Enter your new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character
        
        strcpy(user->email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"john_doe", "old_email@example.com", "securePassword123"};

    printf("User login system\n");

    login(&user);

    return 0;
}