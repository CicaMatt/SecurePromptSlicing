#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("GET /login\n");
}

void do_login() {
    printf("POST /do_login\n");
}

void index() {
    printf("GET /\n");
}

void user_page() {
    printf("GET /user\n");
}

void admin_page() {
    printf("GET /admin\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <function_name>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "login") == 0) {
        login();
    } else if (strcmp(argv[1], "do_login") == 0) {
        do_login();
    } else if (strcmp(argv[1], "index") == 0) {
        index();
    } else if (strcmp(argv[1], "user_page") == 0) {
        user_page();
    } else if (strcmp(argv[1], "admin_page") == 0) {
        admin_page();
    } else {
        printf("Unknown function: %s\n", argv[1]);
        return 1;
    }

    return 0;
}