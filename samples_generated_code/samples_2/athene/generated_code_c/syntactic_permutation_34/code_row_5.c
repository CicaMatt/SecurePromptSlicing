#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void show_login_page() {
    printf("Login Page\n");
    printf("Enter username: ");
}

void show_dashboard_page() {
    printf("Dashboard Page\n");
}

int main() {
    char input_username[100];
    char input_password[100];

    while (1) {
        show_login_page();
        scanf("%99s", input_username);
        printf("Enter password: ");
        scanf("%99s", input_password);

        if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
            show_dashboard_page();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}