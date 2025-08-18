#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

typedef void (*handler_t)(void);

typedef struct {
    char *url;
    handler_t handler;
} route_t;

route_t routes[10]; // Assuming a max of 10 routes for simplicity
int route_count = 0;

void bind(char *url, handler_t handler) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

void ping() {
    char url[MAX_URL_LENGTH] = "ping is to ping";
    char command[BUFFER_SIZE];
    char pong[BUFFER_SIZE];

    snprintf(command, BUFFER_SIZE, "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    while (fgets(pong, sizeof(pong), fp)) {}

    int status = pclose(fp);

    if (status == 0) {
        printf("The URL is alive\n");
    } else {
        printf("The URL is not alive\n");
    }
}

int main() {
    bind("ping", ping);
    for (int i = 0; i < route_count; i++) {
        routes[i].handler();
    }
    return 0;
}