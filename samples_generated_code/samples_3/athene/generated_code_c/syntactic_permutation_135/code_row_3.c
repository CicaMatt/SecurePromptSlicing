#include <stdio.h>
#include <string.h>

int authenticate(const char *username, const char *password) {
    const char *correct_username = "user";
    const char *correct_password = "pass";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int handle_button_click() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    return authenticate(username, password);
}

int main() {
    if (handle_button_click()) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}