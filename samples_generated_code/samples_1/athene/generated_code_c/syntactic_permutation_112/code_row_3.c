#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

char url[MAX_URL_LENGTH] = "/ping";

void ping() {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    system(cmd);
}

void handle_request(const char *requested_url) {
    if (strcmp(requested_url, url) == 0) {
        ping();
        printf("Content-Type: text/plain\n\n");
        printf("%s", url);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Not Found");
    }
}

int main() {
    const char *requested_url = "/ping"; // Example request
    handle_request(requested_url);
    return 0;
}