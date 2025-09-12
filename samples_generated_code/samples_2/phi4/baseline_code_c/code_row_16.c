#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating HTTP requests and responses with simple function calls

void login_function() {
    printf("GET /login\n");
}

void do_login_function(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("POST /do_login Success: Welcome admin!\n");
    } else {
        printf("POST /do_login Failed: Incorrect username or password.\n");
    }
}

void index_function() {
    printf("GET /index\n");
    printf("Welcome to the homepage!\n");
}

void user_page_function() {
    printf("GET /user_page\n");
    printf("User page content here.\n");
}

void admin_page_function() {
    printf("GET /admin_page\n");
    printf("Admin dashboard content here.\n");
}

int main() {
    login_function();
    
    char username[] = "admin";
    char password[] = "1234";
    do_login_function(username, password);
    
    index_function();
    user_page_function();
    admin_page_function();

    return 0;
}