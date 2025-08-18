#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void show_login_page() {
    printf("Login Page\n");
    printf("==========\n");
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        show_login_page();
    }
}

void show_dashboard() {
    printf("\nDashboard\n");
    printf("=========\n");
    printf("Welcome to the dashboard!\n");
}

int main() {
    show_login_page();
    return 0;
}