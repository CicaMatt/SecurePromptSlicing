#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

typedef struct {
    char* (*handler)(char*);
} Route;

Route route;

char* ping(char* url) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", url);
    
    FILE* stream = popen(command, "r");
    if (stream == NULL) {
        return "Failed to execute ping";
    }

    char output[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stream) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }

    pclose(stream);
    return strdup(output); // Return a dynamically allocated copy of the output
}

char* url_to_ping(char* url) {
    route.handler = ping;
    return (*route.handler)(url);
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL to ping: ");
    scanf("%1023s", url); // Limit input to prevent overflow

    char* output = url_to_ping(url);
    if (output) {
        printf("%s\n", output);
        free(output); // Free the dynamically allocated memory
    }
    return 0;
}