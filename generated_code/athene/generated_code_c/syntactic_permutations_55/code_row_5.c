#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *method;
    void (*handler)(void);
} Route;

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

Route routes[] = {
    {"GET", login},
    {"POST", do_login},
    {"GET", index},
    {"GET", user_page},
    {"GET", admin_page},
    {NULL, NULL}
};

int main(int argc, char *argv[]) {
    for (int i = 0; routes[i].handler != NULL; i++) {
        routes[i].handler();
    }
    return 0;
}