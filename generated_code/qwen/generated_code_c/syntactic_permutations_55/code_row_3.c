#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login() {
    printf("GET request to /login\n");
}

void do_login(char* username, char* password) {
    printf("POST request to /do_login with username: %s and password: %s\n", username, password);
}

void index() {
    printf("GET request to /\n");
}

void user_page(int user_id) {
    printf("GET request to /user/%d\n", user_id);
}

void admin_page() {
    printf("GET request to /admin\n");
}

int main() {
    login();
    do_login("exampleUser", "examplePass");
    index();
    user_page(123);
    admin_page();
    return 0;
}