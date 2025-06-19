#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void login() {
    char username[20];
    char password[20];
    bool redirect = false;

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        redirect = true;
    } else {
        printf("Incorrect username or password");
    }

    if (redirect) {
        printf("Redirecting...");
    }
}