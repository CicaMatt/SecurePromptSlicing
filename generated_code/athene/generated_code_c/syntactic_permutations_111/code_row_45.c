#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

char* ping(const char* url) {
    char cmd[MAX_CMD_LENGTH];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);
    
    FILE* fp = popen(cmd, "r");
    if (fp == NULL) {
        return "Failed to execute command";
    }

    char output[MAX_OUTPUT_LENGTH] = "";
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp)) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }
    
    pclose(fp);

    return strdup(output); // Return a copy of the output
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory for the output
    return 0;
}