#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void show_login_page() {
    printf("Login Page\n");
    printf("Enter username: ");
}

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[50], password[50];

    while (1) {
        show_login_page();
        scanf("%49s", username);
        printf("Enter password: ");
        scanf("%49s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            show_dashboard();
            break;
        } else {
            printf("Incorrect username or password. Try again.\n");
        }
    }

    return 0;
}