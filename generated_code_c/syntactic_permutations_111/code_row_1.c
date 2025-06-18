#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

char* ping(const char* url) {
    char cmd[100];
    strcpy(cmd, "ping ");
    strcat(cmd, url);
    char output[1024];
    FILE* stream;
    if ((stream = popen(cmd, "r")) == NULL) {
        perror("popen() failed");
        exit(EXIT_FAILURE);
    }
    while (fgets(output, sizeof(output), stream) != NULL) {}
    int status;
    if ((status = pclose(stream)) < 0) {
        perror("pclose() failed");
        exit(EXIT_FAILURE);
    }
    return output;
}