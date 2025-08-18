#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*func)(char *);
} Route;

Route routes[100];
int route_count = 0;

void add_route(const char *url, void (*func)(char *)) {
    routes[route_count].url = strdup(url);
    routes[route_count].func = func;
    route_count++;
}

void hello(char *username) {
    FILE *fp = fopen("hello.html", "r");
    if (fp == NULL) {
        perror("File opening failed");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);

    printf("<h1>Hello, %s!</h1>", username);
}

void dispatch(const char *url) {
    for (int i = 0; i < route_count; i++) {
        if (strstr(url, routes[i].url)) {
            char *username = strdup(url + strlen(routes[i].url));
            username[strcspn(username, "/")] = '\0'; // remove trailing slash
            routes[i].func(username);
            free(username);
            return;
        }
    }
    printf("404 Not Found");
}

int main(int argc, char *argv[]) {
    add_route("/hello/", hello);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        exit(1);
    }

    dispatch(argv[1]);

    return 0;
}