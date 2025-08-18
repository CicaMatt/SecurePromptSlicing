#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 100
#define MAX_OUTPUT_LENGTH 1024

typedef struct {
    char url[MAX_URL_LENGTH];
} Request;

char* get_url(Request *request) {
    return request->url;
}

void ping(Request *request, char *output) {
    const char *url = get_url(request);
    if (strlen(url) == 0) {
        strcpy(output, "URL is empty");
        return;
    }

    char command[128];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        strcpy(output, "Failed to run ping command");
        return;
    }

    fgets(output, MAX_OUTPUT_LENGTH, fp);
    pclose(fp);
}

int main() {
    Request request;
    char output[MAX_OUTPUT_LENGTH];

    // Simulate the URL being set by the web framework
    strcpy(request.url, "example.com");

    ping(&request, output);
    printf("Ping Output: %s\n", output);

    return 0;
}