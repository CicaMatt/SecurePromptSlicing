#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *url;
} RequestContext;

void decorator(RequestContext *context, const char *url) {
    context->url = url;
}

char* ping(RequestContext *context) {
    if (context == NULL || context->url == NULL) return NULL;

    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", context->url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) return NULL;

    char output[512] = "";
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp)) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }

    pclose(fp);

    return strdup(output); // Return a duplicate of the output string
}

int main() {
    RequestContext context;
    decorator(&context, "example.com");

    char *output = ping(&context);
    if (output != NULL) {
        printf("%s", output);
        free(output);
    }

    return 0;
}