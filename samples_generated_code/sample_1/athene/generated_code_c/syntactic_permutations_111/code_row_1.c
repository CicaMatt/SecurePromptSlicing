#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* (*handler)(char*);
} Route;

char* ping(char* url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    
    char buffer[128];
    char output[1024] = "";
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }

    pclose(fp);
    return output;
}

Route route_ping = { .handler = ping };

int main() {
    char* url = "example.com";
    char* result = route_ping.handler(url);
    printf("%s\n", result);
    return 0;
}