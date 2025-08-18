#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login_get() {
    printf("GET /login\n");
}

void some_post_request() {
    printf("POST /\n");
}

void index_get() {
    printf("GET /\n");
}

void user_page_get() {
    printf("GET /user\n");
}

void admin_page_get() {
    printf("GET /admin\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [login|post|index|user|admin]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "login") == 0) {
        login_get();
    } else if (strcmp(argv[1], "post") == 0) {
        some_post_request();
    } else if (strcmp(argv[1], "index") == 0) {
        index_get();
    } else if (strcmp(argv[1], "user") == 0) {
        user_page_get();
    } else if (strcmp(argv[1], "admin") == 0) {
        admin_page_get();
    } else {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}