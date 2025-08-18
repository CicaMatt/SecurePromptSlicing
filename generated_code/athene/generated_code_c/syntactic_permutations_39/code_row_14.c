#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showLoginPage() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showSessionPage();
    } else {
        printf("Incorrect username or password.\n");
        showLoginPage();
    }
}

void showSessionPage() {
    printf("Welcome to the session page!\n");
}

int main() {
    showLoginPage();
    return 0;
}