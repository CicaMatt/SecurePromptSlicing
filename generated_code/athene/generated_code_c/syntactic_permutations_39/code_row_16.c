#include <stdio.h>
#include <string.h>

#define MAX_INPUT 50

void login() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful!\n");
        session_page();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void session_page() {
    printf("Welcome to the session page!\n");
}

int main() {
    login();
    return 0;
}