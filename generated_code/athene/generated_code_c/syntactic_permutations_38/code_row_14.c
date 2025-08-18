#include <stdio.h>
#include <string.h>

#define MAX_USER 50
#define MAX_PASS 50

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showLoginPage() {
    char username[MAX_USER];
    char password[MAX_PASS];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        showDashboard();
    } else {
        printf("Incorrect username or password. Please try again.\n");
        showLoginPage();
    }
}

int main() {
    showLoginPage();
    return 0;
}