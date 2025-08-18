#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024] = {0};
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Do nothing, output is already captured
    }
    pclose(fp);

    char *result = malloc(strlen(output) + 1);
    strcpy(result, output);
    return result;
}

int main() {
    const char* url = "google.com";
    char* result = ping(url);
    printf("Ping Output:\n%s\n", result);
    free(result);
    return 0;
}