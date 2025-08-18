#include <stdio.h>
#include <stdlib.h>

void ping_url(const char *url) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping %s", url);
    
    printf("URL: %s\n", url);
    system(cmd);
}

int main() {
    const char *url = "google.com";
    ping_url(url);

    return 0;
}