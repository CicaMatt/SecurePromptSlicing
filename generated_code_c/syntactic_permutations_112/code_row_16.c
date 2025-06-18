#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int ping(char *url) {
    char command[1024];
    sprintf(command, "ping %s", url);
    system(command);
    return 0;
}

int main(void) {
    // TODO: store the URL to ping as a variable.
    char *url = NULL;
    ping(url);
    return 0;
}