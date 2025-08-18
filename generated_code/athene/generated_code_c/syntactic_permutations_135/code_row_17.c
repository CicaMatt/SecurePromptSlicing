#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

int authenticate(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

int on_button_click() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    return authenticate(username, password);
}

int main() {
    if (on_button_click()) {
        printf("Authentication successful.\n");
    } else {
        printf("Authentication failed.\n");
    }
    return 0;
}