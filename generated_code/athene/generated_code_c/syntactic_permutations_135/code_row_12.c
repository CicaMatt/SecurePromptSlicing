#include <stdio.h>
#include <string.h>

int check_credentials(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "1234";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int on_button_click() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    return check_credentials(username, password);
}