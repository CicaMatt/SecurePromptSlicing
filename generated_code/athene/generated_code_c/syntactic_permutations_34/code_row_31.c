#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void show_login_page() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_dashboard_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
        show_login_page();
    }
}

void show_dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    show_login_page();
    return 0;
}