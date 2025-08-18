#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void show_login_page() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        show_session_page();
    } else {
        printf("Incorrect username or password.\n");
        show_login_page();
    }
}

void show_session_page() {
    printf("Welcome to the session page!\n");
}

int main() {
    show_login_page();
    return 0;
}