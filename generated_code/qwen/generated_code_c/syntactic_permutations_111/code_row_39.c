#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char* output = malloc(1024);
    output[0] = '\0';

    while (fgets(command, sizeof(command), fp) != NULL) {
        strcat(output, command);
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "example.com"; // URL to ping
    char* result = ping(url);
    printf("Ping Output:\n%s\n", result);
    free(result); // Free the allocated memory for the ping output
    return 0;
}