#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void show_login_page() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_dashboard();
    } else {
        printf("Invalid credentials. Please try again.\n");
        show_login_page();
    }
}

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    show_login_page();
    return 0;
}