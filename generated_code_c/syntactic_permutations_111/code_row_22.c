#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

char *ping(const char *url) {
    int pid, status;
    char *output = malloc(sizeof(char) * 1024);
    if ((pid = fork()) == 0) {
        sprintf(output, "ping %s", url);
        system(output);
    } else {
        wait(&status);
    }
    return output;
}