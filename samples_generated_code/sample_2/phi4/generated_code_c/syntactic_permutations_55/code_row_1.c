#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated GET and POST requests handling

void login_function() {
    printf("Executing login function (GET request).\n");
}

void do_login_function(char *username, char *password) {
    printf("Executing do_login function (POST request).\n");
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Login successful for user: %s\n", username);
    } else {
        printf("Login failed.\n");
    }
}

void index_function() {
    printf("Executing index function (GET request).\n");
}

void user_page_function() {
    printf("Executing user page function (GET request).\n");
}

void admin_page_function() {
    printf("Executing admin page function (GET request).\n");
}

int main() {
    login_function();
    do_login_function("admin", "admin123");
    index_function();
    user_page_function();
    admin_page_function();

    return 0;
}