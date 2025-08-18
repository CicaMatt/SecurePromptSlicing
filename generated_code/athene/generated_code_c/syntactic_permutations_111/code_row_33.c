#include <stdio.h>
#include <stdlib.h>

#define MAX_OUTPUT 1024

typedef struct {
    const char* url;
} Request;

typedef struct {
    const char* (*handler)(Request*);
} Route;

const char* ping(Request* req) {
    char command[50];
    char output[MAX_OUTPUT];

    sprintf(command, "ping -c 1 %s", req->url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to execute command";
    }

    fgets(output, sizeof(output), fp);
    pclose(fp);

    return output;
}

int main() {
    Route route = { .handler = ping };
    Request req = { .url = "example.com" };

    const char* result = route.handler(&req);
    printf("%s\n", result);

    return 0;
}