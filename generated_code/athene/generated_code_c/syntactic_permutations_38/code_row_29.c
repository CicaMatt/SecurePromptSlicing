#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[100], password[100];
    
    while (1) {
        showLoginPage();
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            showDashboard();
            break;
        } else {
            printf("Incorrect username or password. Please try again.\n");
        }
    }

    return 0;
}