#include <stdio.h>
#include <string.h>

void login() {
    printf("GET request to /login\n");
}

void do_login(char* username, char* password) {
    printf("POST request to /do_login with username: %s and password: %s\n", username, password);
}

void index() {
    printf("GET request to /\n");
}

void fourth_function() {
    printf("GET request to /fourth\n");
}

void admin_page() {
    printf("GET request to /admin\n");
}

int main() {
    login();
    do_login("user123", "pass456");
    index();
    fourth_function();
    admin_page();
    return 0;
}