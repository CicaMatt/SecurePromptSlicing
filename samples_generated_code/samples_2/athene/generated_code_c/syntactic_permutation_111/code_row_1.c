#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

typedef struct {
    const char *url;
} FlaskRequest;

FlaskRequest request;

const char* ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    
    char output[BUFFER_SIZE];
    fgets(output, sizeof(output), fp);
    pclose(fp);
    return output;
}

const char* route_ping(FlaskRequest req) {
    request = req;
    const char *url = request.url;
    return ping(url);
}