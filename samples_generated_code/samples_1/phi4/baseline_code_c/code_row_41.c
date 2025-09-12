#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run command\n");
        return -1;
    }

    char buffer[BUFFER_SIZE];
    int isAlive = 0;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strstr(buffer, "1 packets transmitted, 1 received") != NULL) {
            isAlive = 1;
            break;
        }
    }

    pclose(pipe);

    return isAlive ? 0 : -1;
}

void handle_request(const char *url) {
    int pong = ping(url);
    if (pong == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    handle_request(url);

    return 0;
}