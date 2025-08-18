#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }
    ping(argv[1]);
    return 0;
}