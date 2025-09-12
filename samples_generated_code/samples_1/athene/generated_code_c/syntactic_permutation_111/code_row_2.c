#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

typedef struct {
    const char* url;
} Request;

typedef struct {
    const char* (*handler)(Request*);
} Route;

const char* ping(Request* req) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", req->url);
    
    FILE* pipe = popen(command, "r");
    if (!pipe) return "Error: Failed to execute command";

    char output[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, pipe)) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }
    
    pclose(pipe);
    return output;
}

Route routes[] = {
    { .handler = ping },
};

const char* handle_request(const char* url) {
    Request req = { .url = url };
    return routes[0].handler(&req);
}

int main() {
    const char* result = handle_request("example.com");
    printf("%s", result);
    return 0;
}