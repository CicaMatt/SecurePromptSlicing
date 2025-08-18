#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* (*handler)(char*);
} Route;

char* ping(char* url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[256];
    fgets(output, sizeof(output) - 1, fp);
    pclose(fp);
    return output;
}

Route routes[] = {{"ping", ping}};

char* handle_request(char* path, char* url) {
    for (int i = 0; i < sizeof(routes)/sizeof(routes[0]); i++) {
        if (strcmp(routes[i].handler == ping ? "ping" : "", path) == 0) {
            return routes[i].handler(url);
        }
    }
    return "404 Not Found";
}

int main() {
    char* url = "example.com"; // Example URL
    printf("%s\n", handle_request("ping", url));
    return 0;
}