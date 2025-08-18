#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Login failed. Invalid username or password.\n");
    }
}

void show_secret_page() {
    printf("Welcome! Secret settings\n");
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = 0;

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0;

    do_login(input_username, input_password);

    return 0;
}