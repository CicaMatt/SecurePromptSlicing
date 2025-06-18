#include <stdio.h>
#include <string.h>

#define PING_COMMAND "ping -c 3 %s"

char *ping(const char *url)
{
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), PING_COMMAND, url);

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return NULL;
    }

    char output[1024];
    fread(output, sizeof(char), sizeof(output), fp);

    int status = pclose(fp);
    if (status != 0) {
        return NULL;
    }

    return strdup(output);
}