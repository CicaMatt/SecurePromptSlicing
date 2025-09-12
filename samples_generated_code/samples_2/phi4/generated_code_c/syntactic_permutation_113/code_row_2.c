#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executePing(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run command\n" );
        return;
    }

    char buffer[128];
    int alive = 0;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strstr(buffer, "1 packets transmitted") && strstr(buffer, "1 received")) {
            alive = 1;
            break;
        }
    }

    pclose(pipe);

    if (alive) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main() {
    char *url = "google.com"; // Example URL
    executePing(url);
    return 0;
}