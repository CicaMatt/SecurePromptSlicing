#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        return 1;
    }
    return 0;
}

void on_button_click() {
    char username[100];
    char password[100];

    // Simulate getting input from a form
    scanf("%99s", username);
    scanf("%99s", password);

    if (check_mod(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials.\n");
    }
}