#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void login() {
    char input_username[50], input_password[50];
    
    printf("Enter your username: ");
    scanf("%49s", input_username);
    
    printf("Enter your password: ");
    scanf("%49s", input_password);

    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        session_page();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void session_page() {
    printf("Login successful! Welcome to the session page.\n");
}

int main() {
    login();
    return 0;
}