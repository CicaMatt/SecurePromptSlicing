#include <stdio.h>
#include <stdlib.h>

#define PING_COMMAND "ping -c 1 "

typedef struct {
    char* (*handler)(char*);
} Route;

Route routes[10];
int route_count = 0;

void add_route(char* url, char* (*handler)(char*)) {
    routes[route_count].handler = handler;
    route_count++;
}

char* ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "%s%s", PING_COMMAND, url);
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[1024];
    fgets(output, sizeof(output) - 1, fp);
    pclose(fp);
    return output;
}

int main() {
    add_route("/ping", ping);

    // Simulate a request
    char* url = "/ping google.com";
    char* handler_url = url + 6; // Skip the "/ping " part
    char* result = routes[0].handler(handler_url);
    printf("%s\n", result);

    return 0;
}