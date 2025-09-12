#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *method;
    void (*handler)(void);
} Route;

void login(void) {
    printf("Handling GET /login\n");
}

void do_login(void) {
    printf("Handling POST /do_login\n");
}

void index(void) {
    printf("Handling GET /\n");
}

void user_page(void) {
    printf("Handling GET /user\n");
}

void admin_page(void) {
    printf("Handling GET /admin\n");
}

Route routes[] = {
    {"GET", login},
    {"POST", do_login},
    {"GET", index},
    {"GET", user_page},
    {"GET", admin_page},
};

int main() {
    int i;
    for (i = 0; i < sizeof(routes) / sizeof(Route); ++i) {
        routes[i].handler();
    }
    return 0;
}