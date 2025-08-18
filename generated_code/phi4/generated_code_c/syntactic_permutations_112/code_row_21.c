#include <stdio.h>
#include <stdlib.h>

char url[] = "<your-url-here>";

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Executing: %s\n", command);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "ping") == 0) {
        ping();
    } else {
        printf("Usage: %s ping\n", argv[0]);
    }
    return 0;
}