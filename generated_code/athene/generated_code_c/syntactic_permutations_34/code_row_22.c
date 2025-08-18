#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void show_login_page() {
    printf("Login Page\n");
    char username[100];
    char password[100];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

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