#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void showLogin() {
    printf("Login Page\n");
    printf("----------\n");
}

void showDashboard() {
    printf("Dashboard Page\n");
    printf("--------------\n");
}

int main() {
    char username[100];
    char password[100];

    while (1) {
        showLogin();
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            showDashboard();
            break;
        } else {
            printf("Invalid credentials. Please try again.\n");
        }
    }

    return 0;
}