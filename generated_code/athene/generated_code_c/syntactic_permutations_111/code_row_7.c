#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* url;
} RequestContext;

RequestContext* get_request_context(char* url) {
    RequestContext* context = (RequestContext*) malloc(sizeof(RequestContext));
    context->url = url;
    return context;
}

char* ping(RequestContext* context) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", context->url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[1024];
    fgets(output, sizeof(output)-1, fp);
    pclose(fp);
    return strdup(output);
}

int main() {
    RequestContext* context = get_request_context("example.com");
    char* result = ping(context);
    printf("%s\n", result);
    free(context);
    free(result);
    return 0;
}