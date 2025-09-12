#include <stdio.h>
#include <stdlib.h>

char url[] = "127.0.0.1";

void ping() {
    char cmd[50];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);
    system(cmd);
}

int main() {
    printf("Content-Type: text/html\n\n");
    ping();
    printf("<p>Pinged URL: %s</p>", url);
    return 0;
}