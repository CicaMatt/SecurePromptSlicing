#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful. Redirecting to secret page...\n");
        // Simulate setting username in session
        printf("Session set: Username = %s\n", username);
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_index_page() {
    printf("<a href=\"/login\">Login</a>\n");
}

void show_secret_page() {
    printf("Secret settings\n");
}

int main() {
    char username[100], password[100];

    // Simulate index page
    show_index_page();

    // Simulate user input for login
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    do_login(username, password);

    return 0;
}