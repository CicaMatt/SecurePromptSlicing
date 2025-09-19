#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

typedef struct {
    const char *url;
} Request;

typedef struct {
    const char *output;
} Response;

Response ping(Request req) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", req.url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return (Response){.output = "Failed to execute ping"};
    }

    char buffer[BUFFER_SIZE];
    Response res;
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        if (res.output == NULL) {
            res.output = strdup(buffer);
        } else {
            res.output = realloc(res.output, strlen(res.output) + strlen(buffer) + 1);
            strcat(res.output, buffer);
        }
    }

    pclose(fp);
    return res;
}

int main() {
    Request req = (Request){.url = "example.com"};
    Response res = ping(req);
    printf("%s", res.output);
    free((void *)res.output);
    return 0;
}