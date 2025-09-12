#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*func)(char*);
} Route;

Route routes[10];
int route_count = 0;

void add_route(char* url, void (*func)(char*)) {
    routes[route_count].url = url;
    routes[route_count].func = func;
    route_count++;
}

void render_template(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf(buffer);
        if (strstr(buffer, "{{ username }}")) {
            printf("%s", username);
        }
    }
    fclose(file);
}

void hello(char* username) {
    render_template("hello.html", username);
}

void route_dispatcher(char* url, char* param) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].func(param);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello", hello);

    char url[100], param[100];
    scanf("%s %s", url, param);
    route_dispatcher(url, param);

    return 0;
}