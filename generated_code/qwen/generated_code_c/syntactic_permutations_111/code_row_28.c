#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_LENGTH 256
#define OUTPUT_BUFFER_SIZE 1024

char* ping(char* url) {
    char command[URL_LENGTH + 7]; // "ping " + URL + '\0'
    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp;
    char output[OUTPUT_BUFFER_SIZE];
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Do nothing, the output buffer will contain the last line of the ping result
    }
    pclose(fp);

    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(result, output);
    return result;
}

int main() {
    char url[] = "example.com"; // This would be dynamically obtained in a real web app
    char *output = ping(url);
    printf("%s", output);
    free(output);
    return 0;
}