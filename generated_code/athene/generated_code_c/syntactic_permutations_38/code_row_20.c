#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void show_login_page() {
    printf("Login Failed. Please try again.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_dashboard();
    } else {
        show_login_page();
    }

    return 0;
}