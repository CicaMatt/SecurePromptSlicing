#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* url;
} Request;

void decorator(Request* request, void (*func)(Request*)) {
    func(request);
}

void ping(Request* request) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", request->url);
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("Failed to run command\n");
        exit(1);
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
}

int main() {
    Request request;
    request.url = "example.com";
    decorator(&request, ping);
    return 0;
}