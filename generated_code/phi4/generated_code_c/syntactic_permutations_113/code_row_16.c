#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        printf("Failed to run command\n");
        return;
    }

    char buffer[128];
    char pong[1024] = {0};
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(pong, buffer);
    }

    int status = pclose(pipe);

    if (status == 0) {
        printf("URL %s is alive\n", url);
    } else {
        printf("URL %s is not alive\n", url);
    }
}

int main() {
    const char *url = "8.8.8.8"; // Example URL to ping
    ping(url);
    return 0;
}