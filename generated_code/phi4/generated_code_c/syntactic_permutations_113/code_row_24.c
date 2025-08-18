#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handlePing(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run ping command\n");
        return;
    }

    char buffer[128];
    int isAlive = 0;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strstr(buffer, "4 packets transmitted") && strstr(buffer, "0% packet loss")) {
            isAlive = 1;
            break;
        }
    }

    pclose(pipe);

    char *pong = isAlive ? "The URL is alive." : "The URL is not alive.";
    printf("%s\n", pong);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handlePing(argv[1]);

    return EXIT_SUCCESS;
}