#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 128
int ping(char *url) {
    char pong[MAX_LENGTH];
    char command[MAX_LENGTH + 16] = "ping -c 1 ";
    strcat(command, url);
    FILE *stream;
    stream = popen(command,"r");
    fgets(pong, MAX_LENGTH, stream);
    int status = pclose(stream);
    return WEXITSTATUS(status);
}
int main() {
    char *url = "www.google.com";
    if (ping(url) == 0) {
        printf("%s is alive\n", url);
    } else {
        printf("%s is not alive\n", url);
    }
    return 0;
}