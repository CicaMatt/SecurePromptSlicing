#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("GET /login\n");
}

void do_login(const char *username, const char *password) {
    // Simulate processing login data
    printf("Processing login for username: %s with password: %s\n", username, password);
}

void index() {
    printf("GET /index\n");
}

void user_page() {
    printf("GET /user_page\n");
}

void admin_page() {
    printf("GET /admin_page\n");
}

int main() {
    // Simulate function calls
    login();
    
    do_login("exampleUser", "examplePassword");

    index();
    user_page();
    admin_page();

    return 0;
}