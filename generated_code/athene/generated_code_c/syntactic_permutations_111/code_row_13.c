#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* url;
} Route;

Route route(char* url) {
    Route r = {url};
    return r;
}

char* ping(Route r) {
    FILE *fp;
    char output[1024];
    char command[1024];
    snprintf(command, sizeof(command), "ping -c 4 %s", r.url);
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Collect the output
    }
    pclose(fp);
    return strdup(output); // Return a copy of the last line of ping output
}

int main() {
    Route r = route("google.com");
    char* result = ping(r);
    printf("%s", result);
    free(result);
    return 0;
}