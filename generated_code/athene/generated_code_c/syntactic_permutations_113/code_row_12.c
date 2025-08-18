#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*func_ptr)(void);

typedef struct {
    char *url;
    func_ptr func;
} Route;

Route routes[100];
int route_count = 0;

void add_route(const char *url, func_ptr func) {
    routes[route_count].url = strdup(url);
    routes[route_count].func = func;
    route_count++;
}

char pong[1024];

void ping() {
    FILE *fp;
    char command[50];
    snprintf(command, sizeof(command), "ping -c 1 %s", "url");
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {}
    pclose(fp);
    if (WIFEXITED(0) && WEXITSTATUS(0) == 0) {
        printf("URL is alive.\n");
    } else {
        printf("URL is not alive.\n");
    }
}

int main() {
    add_route("/ping", ping);
    // Simulate calling the route
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(routes[i].url, "/ping") == 0) {
            routes[i].func();
            break;
        }
    }
    return 0;
}