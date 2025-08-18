#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*Handler)(const char*);

void bind_url(const char* url, Handler handler) {
    printf("Binding URL '%s' to function\n", url);
}

void ping(const char* url) {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Collect output
    }
    pclose(fp);

    int status = WEXITSTATUS(system(cmd));
    if (status == 0) {
        printf("URL '%s' is alive\n", url);
    } else {
        printf("URL '%s' is not alive\n", url);
    }
}

int main() {
    const char* url = "example.com";
    bind_url(url, ping);
    ping(url);
    return 0;
}