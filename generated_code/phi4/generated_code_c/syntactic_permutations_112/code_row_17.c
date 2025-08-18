#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executePing(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    printf("Executing: %s\n", command);
    
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Error executing ping command.\n");
    } else {
        printf("Ping command executed successfully.\n");
    }
}

void handleRequest(const char *requestUrl) {
    if (strncmp(requestUrl, "/ping ", 6) == 0) {
        const char *url = requestUrl + 6;
        
        if (strlen(url) > 0) {
            executePing(url);
        } else {
            fprintf(stderr, "No URL provided for ping.\n");
        }
    } else {
        printf("Invalid request. Use /ping <url> to execute ping command.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <requestUrl>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handleRequest(argv[1]);

    return EXIT_SUCCESS;
}