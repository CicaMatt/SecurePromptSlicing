#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

typedef struct {
    char* (*handler)(char*);
} Route;

char* ping(char* url) {
    char command[MAX_URL_LENGTH + 32];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to execute ping";
    }
    char output[MAX_OUTPUT_LENGTH];
    fgets(output, sizeof(output), fp);
    pclose(fp);
    return strdup(output);
}

char* route_handler(char* url) {
    return ping(url);
}

int main() {
    Route route = { .handler = route_handler };
    char url[MAX_URL_LENGTH] = "example.com"; // Example URL
    char* output = route.handler(url);
    printf("%s\n", output);
    free(output);
    return 0;
}