#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        sessionPage();
    } else {
        printf("The username or password is incorrect.\n");
    }
}

void sessionPage() {
    printf("Welcome to the session page!\n");
}

int main() {
    loginPage();
    return 0;
}