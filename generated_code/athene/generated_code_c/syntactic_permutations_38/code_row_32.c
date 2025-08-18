#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showLogin() {
    printf("Username: ");
    char username[50];
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Password: ");
    char password[50];
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showDashboard();
    } else {
        printf("Invalid username or password.\n");
        showLogin();
    }
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    showLogin();
    return 0;
}