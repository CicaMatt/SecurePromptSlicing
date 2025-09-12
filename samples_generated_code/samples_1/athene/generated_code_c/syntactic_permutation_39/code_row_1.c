#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
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