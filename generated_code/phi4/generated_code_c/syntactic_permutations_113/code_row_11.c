#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_url_alive(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "curl -s -o /dev/null -w \"%{http_code}\" %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        return;
    }

    char pong[16];
    if (fgets(pong, sizeof(pong), fp) != NULL) {
        pong[strcspn(pong, "\n")] = '\0'; // Remove newline character
        int http_code = atoi(pong);
        if (http_code == 200) {
            printf("URL %s is alive.\n", url);
        } else {
            printf("URL %s is not alive. HTTP Code: %d\n", url, http_code);
        }
    }

    pclose(fp);
}

int main() {
    char *url = "http://example.com";
    check_url_alive(url);

    return 0;
}