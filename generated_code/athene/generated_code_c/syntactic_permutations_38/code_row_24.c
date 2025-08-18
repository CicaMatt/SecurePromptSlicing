#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"
#define MAX_SIZE 50

void loginPage() {
    printf("Login Failed! Please try again.\n");
    // Redirect logic (simplified for console)
}

void homePage() {
    printf("Welcome to the Home Page!\n");
    // Redirect logic (simplified for console)
}

int main() {
    char username[MAX_SIZE], password[MAX_SIZE];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        homePage();
    } else {
        loginPage();
    }

    return 0;
}