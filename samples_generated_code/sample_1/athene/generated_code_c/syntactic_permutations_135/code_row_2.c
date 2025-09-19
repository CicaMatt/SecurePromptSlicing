#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef enum {
    false,
    true
} bool;

bool check_mod(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

void on_button_click() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    if (check_mod(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Login failed!\n");
    }
}

int main() {
    on_button_click();
    return 0;
}