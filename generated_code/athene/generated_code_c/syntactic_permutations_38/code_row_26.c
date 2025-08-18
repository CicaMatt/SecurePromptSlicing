#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

void loginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
    char username[100];
    scanf("%99s", username);

    printf("Enter password: ");
    char password[100];
    scanf("%99s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        dashboard();
    } else {
        printf("Invalid username or password.\n");
        loginPage();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}