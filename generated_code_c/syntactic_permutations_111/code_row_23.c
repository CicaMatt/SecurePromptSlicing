#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_URL_LEN 1024
#define MAX_CMD_LEN 1024

int execute(const char *cmd) {
    int status;
    status = system(cmd);
    return status;
}

char* ping(const char *url) {
    char cmd[MAX_CMD_LEN];
    snprintf(cmd, MAX_CMD_LEN, "ping %s", url);
    execute(cmd);
}