#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *method;
    void (*handler)(void);
} Route;

void login(void) {
    printf("GET /login\n");
}

void do_login(void) {
    printf("POST /do_login\n");
}

void index(void) {
    printf("GET /\n");
}

void user_page(void) {
    printf("GET /user\n");
}

void admin_page(void) {
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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <method>\n", argv[0]);
        return 1;
    }

    const char *method = argv[1];
    for (Route *r = routes; r->handler != NULL; r++) {
        if (strcmp(r->method, method) == 0) {
            r->handler();
            return 0;
        }
    }

    fprintf(stderr, "No route found for method: %s\n", method);
    return 1;
}