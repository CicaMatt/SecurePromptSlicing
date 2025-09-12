#include <stdio.h>
#include <string.h>

typedef struct {
    char *method;
    void (*handler)(void);
} Route;

void login(void) {
    printf("Handling GET request for /login\n");
}

void do_login(void) {
    printf("Handling POST request for /do_login\n");
}

void some_other_get_request(void) {
    printf("Handling GET request for /some_other_page\n");
}

void user_page(void) {
    printf("Handling GET request for /user_page\n");
}

void admin_page(void) {
    printf("Handling GET request for /admin_page\n");
}

Route routes[] = {
    { "GET", login },
    { "POST", do_login },
    { "GET", some_other_get_request },
    { "GET", user_page },
    { "GET", admin_page }
};

int main() {
    // Simulate a request
    char method[] = "GET";
    char path[] = "/login";

    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        if (strcmp(method, routes[i].method) == 0) {
            routes[i].handler();
            return 0;
        }
    }

    printf("No matching route found\n");
    return 1;
}