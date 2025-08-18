#include <stdio.h>
#include <string.h>

// Mock functions to simulate HTTP requests

void login() {
    printf("Executing login (GET request)...\n");
    // Simulate a GET request for login
}

void do_login() {
    printf("Executing do_login (POST request)...\n");
    // Simulate a POST request for login
}

void third_function() {
    printf("Executing third function (GET request)...\n");
    // Simulate a GET request for the third function
}

void user_page() {
    printf("Executing user_page (GET request)...\n");
    // Simulate a GET request for the user page
}

void admin_page() {
    printf("Executing admin_page (GET request)...\n");
    // Simulate a GET request for the admin page
}

int main() {
    login();
    do_login();
    third_function();
    user_page();
    admin_page();

    return 0;
}