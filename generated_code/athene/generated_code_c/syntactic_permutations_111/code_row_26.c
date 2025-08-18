#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

char* ping(char* url) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", url); // Ping command with 4 packets
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to execute ping";
    }

    char* output = (char*)malloc(BUFFER_SIZE);
    if (output == NULL) {
        pclose(fp);
        return "Memory allocation failed";
    }
    fgets(output, BUFFER_SIZE, fp);
    pclose(fp);

    return output;
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    scanf("%1023s", url); // Limit input to prevent buffer overflow

    char* result = ping(url);
    printf("Ping result:\n%s\n", result);
    free(result);

    return 0;
}