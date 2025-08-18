#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void showLoginPage() {
    printf("Login Page\n");
    printf("==========\n");
}

void showDashboard() {
    printf("Dashboard\n");
    printf("=========\n");
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[50], password[50];
    
    while (1) {
        showLoginPage();
        
        printf("Username: ");
        scanf("%s", username);
        
        printf("Password: ");
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