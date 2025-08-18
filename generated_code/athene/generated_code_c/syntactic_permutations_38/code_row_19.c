#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void show_login_page() {
    printf("Login Page\n");
    printf("==========\n");
}

void show_dashboard() {
    printf("Dashboard\n");
    printf("=========\n");
}

int main() {
    char username[50], password[50];

    show_login_page();
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_dashboard();
    } else {
        show_login_page();
        printf("Invalid username or password.\n");
    }

    return 0;
}