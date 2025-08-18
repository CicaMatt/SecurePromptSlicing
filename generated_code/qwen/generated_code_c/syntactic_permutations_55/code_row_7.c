#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_request() {
    printf("Handling GET request\n");
}

void do_login() {
    printf("Handling POST request for login\n");
}

void index() {
    printf("Handling GET request for index\n");
}

void user_page() {
    printf("Handling GET request for user page\n");
}

void admin_page() {
    printf("Handling GET request for admin page\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <function_name>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "get_request") == 0) {
        get_request();
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