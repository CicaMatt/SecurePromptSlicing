#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *url = "ping";
    char command[50];

    snprintf(command, sizeof(command), "ping %s", url);
    system(command);

    printf("URL: %s\n", url);
    return 0;
}