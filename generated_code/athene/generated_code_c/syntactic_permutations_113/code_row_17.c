#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_OUTPUT 256

typedef void (*HandlerFunc)(void);

typedef struct {
    char *url;
    HandlerFunc handler;
} Route;

Route routes[10];
int route_count = 0;

void add_route(char *url, HandlerFunc handler) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

char* execute_command(const char* command) {
    static char buffer[MAX_COMMAND_OUTPUT];
    FILE *pipe = popen(command, "r");
    if (!pipe) return "ERROR";
    fgets(buffer, MAX_COMMAND_OUTPUT, pipe);
    pclose(pipe);
    return buffer;
}

void ping() {
    char url[100] = "www.example.com"; // URL to ping
    char command[150];
    sprintf(command, "ping -c 1 %s", url);
    int status = system(command);

    if (status == 0) {
        printf("URL is alive\n");
    } else {
        printf("URL is not alive\n");
    }
}

void handle_request(const char *requested_url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, requested_url) == 0) {
            routes[i].handler();
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("ping", ping);
    handle_request("ping");
    return 0;
}