#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        return;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), pipe) != NULL) {
        // Process output if needed
    }

    int status = pclose(pipe);
    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    const char *url = "google.com";
    ping(url);
    return 0;
}