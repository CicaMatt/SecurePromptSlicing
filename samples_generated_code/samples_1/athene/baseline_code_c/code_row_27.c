#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void show_login_page() {
    printf("Login Page:\n");
    printf("Enter username: ");
}

void show_dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[100];
    char password[100];

    while (1) {
        show_login_page();
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            show_dashboard_page();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}