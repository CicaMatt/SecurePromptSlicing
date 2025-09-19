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
    char username[100];
    char password[100];

    show_login_page();
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_dashboard_page();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        main(); // Simulate redirect by restarting the process
    }

    return 0;
}