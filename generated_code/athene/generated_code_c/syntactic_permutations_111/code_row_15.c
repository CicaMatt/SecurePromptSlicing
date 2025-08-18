#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE* pipe = popen(command, "r");
    if (!pipe) return NULL;
    char buffer[128];
    char output[1024] = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }
    pclose(pipe);
    return strdup(output); // Caller must free the returned string
}