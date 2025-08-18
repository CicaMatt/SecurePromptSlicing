#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping_function(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run command\n");
        return;
    }

    char pong[512] = {0};
    while (fgets(pong, sizeof(pong), pipe) != NULL) {
        printf("%s", pong);
    }
    
    int status = pclose(pipe);
    if (status == 0) {
        printf("The URL %s is reachable.\n", url);
    } else {
        printf("The URL %s is not reachable.\n", url);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    ping_function(url);

    return 0;
}