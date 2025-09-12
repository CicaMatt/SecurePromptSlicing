#include <stdio.h>
#include <stdlib.h>

#define PING_COMMAND "ping -c 4 "

typedef struct {
    char* (*handler)(char*);
} Route;

char* ping(char* url) {
    char command[100];
    snprintf(command, sizeof(command), "%s %s", PING_COMMAND, url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[1024];
    fgets(output, sizeof(output)-1, fp);
    pclose(fp);
    return strdup(output); // Return a copy of the output
}

Route routes[] = {
    { .handler = ping },
};

int main() {
    // Simulate calling the route handler with a URL
    char* url = "example.com";
    Route* route = &routes[0];
    char* result = route->handler(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory for output
    return 0;
}