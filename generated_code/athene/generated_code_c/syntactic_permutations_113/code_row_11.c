#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char url[256] = "http://example.com";
char pong[128];

int check_url(const char *url, char *pong) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "curl -I %s 2>/dev/null | head -n 1", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return 1;
    }
    fgets(pong, sizeof(pong), fp);
    pclose(fp);
    return strcmp(pong, "") == 0 ? 1 : 0;
}

void bind_to_url(const char *url, void (*func)(const char *)) {
    strcpy(url, url);
    func(url);
}

void handle_request(const char *url) {
    if (check_url(url, pong) == 0) {
        printf("URL %s is alive. Response: %s", url, pong);
    } else {
        printf("URL %s is not alive.", url);
    }
}

int main() {
    bind_to_url(url, handle_request);
    return 0;
}