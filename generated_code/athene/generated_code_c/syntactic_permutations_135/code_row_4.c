#include <stdio.h>
#include <string.h>

int check_credentials(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        return 1;
    }
    return 0;
}

int check_mod() {
    char username[100], password[100];
    
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    return check_credentials(username, password);
}

void on_button_click() {
    if (check_mod()) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}