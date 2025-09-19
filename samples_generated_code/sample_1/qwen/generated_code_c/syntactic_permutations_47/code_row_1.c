#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100

typedef void (*FunctionPointer)();

typedef struct {
    char url[MAX_URL_LENGTH];
    FunctionPointer func;
} Route;

Route routes[] = {
    {"http://example.com/home", NULL},
    {"http://example.com/about", NULL}
};

void set_function_for_url(const char *url, FunctionPointer func) {
    for (int i = 0; i < sizeof(routes) / sizeof(Route); i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].func = func;
            break;
        }
    }
}

void trigger_function_for_url(const char *url) {
    for (int i = 0; i < sizeof(routes) / sizeof(Route); i++) {
        if (strcmp(routes[i].url, url) == 0 && routes[i].func != NULL) {
            routes[i].func();
            return;
        }
    }
    printf("No function found for URL: %s\n", url);
}

void home_function() {
    printf("Home page accessed.\n");
}

void about_function() {
    printf("About page accessed.\n");
}

int main() {
    set_function_for_url("http://example.com/home", home_function);
    set_function_for_url("http://example.com/about", about_function);

    trigger_function_for_url("http://example.com/home");
    trigger_function_for_url("http://example.com/about");
    trigger_function_for_url("http://example.com/contact");

    return 0;
}