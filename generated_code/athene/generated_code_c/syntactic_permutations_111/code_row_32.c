#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

typedef struct {
    char* url;
} Request;

typedef struct {
    const char* route;
    void (*handler)(Request*);
} Route;

void ping(Request* request) {
    char command[MAX_URL_LENGTH + 10];
    snprintf(command, sizeof(command), "ping -c 4 %s", request->url);
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        exit(1);
    }
    char output[MAX_OUTPUT_LENGTH];
    fgets(output, MAX_OUTPUT_LENGTH, pipe);
    pclose(pipe);
    printf("%s", output); // Assuming this is how the output should be returned
}

void handle_request(Route* route, Request* request) {
    if (route->handler != NULL) {
        route->handler(request);
    }
}

int main() {
    Route routes[] = {
        {"/ping", ping},
        {"", NULL}
    };
    Request request;
    request.url = "example.com"; // Example URL

    for (Route* r = routes; r->route != NULL; ++r) {
        if (strcmp(r->route, "/ping") == 0) {
            handle_request(r, &request);
            break;
        }
    }

    return 0;
}