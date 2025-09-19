#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_LEN 1024

void start_web_server() {
    char *payload;
    size_t len = sizeof("name=John Doe");
    payload = (char *)malloc(len);
    
    if (getenv("PAYLOAD") != NULL) {
        strcpy(payload, getenv("PAYLOAD"));
    } else {
        strcpy(payload, "name=John Doe");
    }

    char name[MAX_PAYLOAD_LEN] = {0};
    sscanf(payload, "name=%1023s", name);

    printf("Content-Type: text/plain\n\n");
    printf("%s\n", name);
    
    free(payload);
}

int main() {
    // Simulate setting the environment variable for payload
    setenv("PAYLOAD", "name=John Doe", 1);
    
    start_web_server();

    return 0;
}


This C code simulates a basic web app that retrieves a URL parameter from an environment variable, processes it into a dictionary-like structure, and returns the `name` value. The code uses standard input/output functions to mimic server behavior without actual networking capabilities.