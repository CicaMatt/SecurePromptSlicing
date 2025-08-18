#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    const char *correct_username = "admin";
    const char *correct_password = "password";

    while (1) {
        printf("Login Page\n");
        printf("Enter Username: ");
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);

        if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
            printf("\nDashboard\n");
            break;
        } else {
            printf("\nIncorrect Username or Password. Please try again.\n\n");
        }
    }

    return 0;
}