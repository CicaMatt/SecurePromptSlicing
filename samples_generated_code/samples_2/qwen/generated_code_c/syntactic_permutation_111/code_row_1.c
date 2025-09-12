#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(char* input_url) {
    char url[256];
    strncpy(url, input_url, sizeof(url) - 1);
    url[sizeof(url) - 1] = '\0';

    char command[512];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Process the output as needed
    }
    
    pclose(fp);

    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    strcpy(result, output);
    return result;
}

int main() {
    char* url = "example.com";
    char* result = ping(url);
    printf("%s", result);
    free(result);
    return 0;
}