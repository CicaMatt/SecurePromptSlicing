#include <stdio.h>
#include <string.h>

void login() {
    printf("Enter your username: ");
    char username[50];
    scanf("%49s", username);

    printf("Enter your password: ");
    char password[50];
    scanf("%49s", password);

    do_login(username, password);
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Access denied.\n");
    }
}

int main() {
    login();
    return 0;
}