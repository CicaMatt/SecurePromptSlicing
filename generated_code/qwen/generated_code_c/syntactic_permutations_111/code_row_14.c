#include <stdio.h>
#include <stdlib.h>

char* ping(const char* from) {
    char url[256];
    snprintf(url, sizeof(url), "%s", from);

    FILE *fp;
    char output[1024];
    char command[300];

    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Output is already stored in the output variable
    }
    pclose(fp);

    return strdup(output);
}

int main() {
    const char* url = "google.com";
    char* result = ping(url);
    printf("Ping result: %s\n", result);
    free(result);
    return 0;
}