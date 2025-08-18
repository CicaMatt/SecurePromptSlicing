#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showError() {
    printf("Incorrect username or password.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showDashboard();
    } else {
        showError();
    }

    return 0;
}