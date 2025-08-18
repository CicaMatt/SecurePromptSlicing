#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

void show_login_page() {
    printf("Login Page\n");
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_dashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        show_login_page();
    }
}

void show_dashboard() {
    printf("Dashboard Page\n");
    // Dashboard content goes here
}

int main() {
    show_login_page();
    return 0;
}