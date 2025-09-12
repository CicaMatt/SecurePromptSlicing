#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void displayLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
}

void displaySessionPage() {
    printf("Welcome to your session page!\n");
}

int main() {
    char username[50];
    char password[50];

    displayLoginPage();
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        displaySessionPage();
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}