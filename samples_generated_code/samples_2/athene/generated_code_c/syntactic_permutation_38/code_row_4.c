#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showError() {
    printf("Incorrect username or password.\n");
}

int main() {
    char inputUsername[100];
    char inputPassword[100];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        showDashboard();
    } else {
        showError();
    }

    return 0;
}