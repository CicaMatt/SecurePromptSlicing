#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

void on_button_click() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}