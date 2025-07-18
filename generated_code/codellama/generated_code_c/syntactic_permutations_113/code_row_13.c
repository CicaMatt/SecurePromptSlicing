#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static char *ping_command = "ping -c1 -W1 %s";
static char *pong;

void ping(char* url) {
    int status = 0;
    char *cmd = malloc(strlen(url)+strlen(ping_command));
    sprintf(cmd, ping_command, url);
    FILE *fp = popen(cmd, "r");
    free(cmd);
    if (fp == NULL) {
        perror("popen() failed!");
        exit(1);
    }
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        printf("%s", pong);
    }
    status = pclose(fp);
    if (!WIFEXITED(status) || WEXITSTATUS(status)) {
        perror("ping failed!");
        exit(1);
    }
}