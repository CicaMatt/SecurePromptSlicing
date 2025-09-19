#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int check_credentials(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

void on_button_click() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}