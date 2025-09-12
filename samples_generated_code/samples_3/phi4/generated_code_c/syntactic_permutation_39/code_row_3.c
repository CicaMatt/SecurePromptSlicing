#include <stdio.h>
#include <string.h>

void displayLoginPage() {
    char username[50];
    char password[50];
    
    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Welcome to the Session Page!\n");
    // Additional functionality can be added here
}

int main() {
    displayLoginPage();
    return 0;
}