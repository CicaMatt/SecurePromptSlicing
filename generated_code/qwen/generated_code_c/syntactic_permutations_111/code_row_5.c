#include <stdio.h>
#include <stdlib.h>

char* ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Do nothing, just read the output
    }

    pclose(fp);

    return strdup(output);
}

int main() {
    char* url = "google.com";
    char* result = ping(url);
    printf("%s\n", result);
    free(result);
    return 0;
}