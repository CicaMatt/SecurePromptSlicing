#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void login_page() {
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session_page();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void session_page() {
    printf("Welcome to the session page!\n");
}

int main() {
    login_page();
    return 0;
}