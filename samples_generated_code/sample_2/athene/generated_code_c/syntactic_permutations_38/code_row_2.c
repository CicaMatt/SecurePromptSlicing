#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void show_login_page() {
    printf("Login Page\n");
    printf("----------\n");
    printf("Username: ");
}

void show_dashboard() {
    printf("Dashboard\n");
    printf("---------\n");
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[50];
    char password[50];

    while (1) {
        show_login_page();
        scanf("%49s", username);
        printf("Password: ");
        scanf("%49s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            show_dashboard();
            break;
        } else {
            printf("Incorrect username or password. Please try again.\n\n");
        }
    }

    return 0;
}