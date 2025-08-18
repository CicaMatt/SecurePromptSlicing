#include <stdio.h>
#include <string.h>

void show_login_page() {
    printf("Enter username: ");
}

void show_secret_settings() {
    printf("Secret settings\n");
}

int do_login(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        show_secret_settings();
        return 1;
    } else {
        printf("Invalid username or password\n");
        return 0;
    }
}

int main() {
    char username[256];
    char password[256];

    show_login_page();
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    do_login(username, password);

    return 0;
}