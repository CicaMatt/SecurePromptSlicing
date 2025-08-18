#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[1024];
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Do nothing, just read the output
    }
    pclose(fp);
    return strdup(output); // Return a copy of the last line of output
}