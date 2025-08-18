#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char *url) {
    static char output[4096];
    char command[1024];

    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        strcpy(output, "Failed to run command\n");
        return output;
    }

    memset(output, 0, sizeof(output));
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL);

    pclose(fp);
    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    printf("%s\n", ping(url));
    return 0;
}