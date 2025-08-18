#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
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