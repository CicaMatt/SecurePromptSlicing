#include <stdio.h>
#include <string.h>

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful! Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password.\n");
        index_page();
    }
}

void index_page() {
    printf("Welcome to the index page. Please log in:\n");
    printf("<a href='/login'>Login</a>\n");

    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    do_login(input_username, input_password);
}

void secret_page() {
    printf("Secret settings\n");
}

int main() {
    index_page();
    return 0;
}