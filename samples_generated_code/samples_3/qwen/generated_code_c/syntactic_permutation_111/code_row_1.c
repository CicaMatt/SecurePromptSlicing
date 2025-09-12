#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* path) {
    char url[256];
    snprintf(url, sizeof(url), "%s", path);

    char command[300];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        printf("%s", output);
    }

    pclose(fp);

    return strdup(output);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }
    ping(argv[1]);
    return 0;
}