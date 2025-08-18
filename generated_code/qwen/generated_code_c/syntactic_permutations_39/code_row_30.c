#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character
    
    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("\nLogin Successful!\nRedirecting to session page...\n");
        sessionPage();
    } else {
        printf("\nIncorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Welcome to your session page. You are now logged in.\n");
}

int main() {
    printf("Simple Login Page\n");
    loginPage();
    return 0;
}