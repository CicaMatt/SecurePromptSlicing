#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 1024

void login_function() {
    printf("GET /login\n");
}

void do_login_function(const char *username, const char *password) {
    printf("POST /do_login\n");
    printf("Data: username=%s&password=%s\n", username, password);
}

void index_function() {
    printf("GET /\n");
}

void user_page_function() {
    printf("GET /user_page\n");
}

void admin_page_function() {
    printf("GET /admin_page\n");
}

int main() {
    login_function();
    
    const char *username = "test_user";
    const char *password = "test_pass123";

    do_login_function(username, password);

    index_function();

    user_page_function();

    admin_page_function();

    return 0;
}