#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256
#define BUFFER_SIZE 1024

typedef struct {
    char* url;
} RequestContext;

RequestContext* create_request_context(const char* url) {
    RequestContext* ctx = (RequestContext*)malloc(sizeof(RequestContext));
    ctx->url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    snprintf(ctx->url, MAX_URL_LENGTH, "%s", url);
    return ctx;
}

void free_request_context(RequestContext* ctx) {
    free(ctx->url);
    free(ctx);
}

char* ping(RequestContext* ctx) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", ctx->url);

    FILE* pipe = popen(command, "r");
    if (!pipe) return "Failed to run command";

    char buffer[BUFFER_SIZE];
    char* output = (char*)malloc(BUFFER_SIZE * sizeof(char));
    output[0] = '\0';

    while (fgets(buffer, BUFFER_SIZE, pipe)) {
        strncat(output, buffer, BUFFER_SIZE - strlen(output) - 1);
    }

    pclose(pipe);
    return output;
}

int main() {
    const char* url = "example.com";
    RequestContext* ctx = create_request_context(url);
    char* result = ping(ctx);
    printf("%s", result);
    free(result);
    free_request_context(ctx);
    return 0;
}