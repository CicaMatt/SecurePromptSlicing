#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_credentials(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void on_button_click() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}