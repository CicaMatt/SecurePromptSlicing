#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_url_alive(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "curl -s --head %s | grep \"200 OK\"", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        return -1;
    }

    int alive = 0;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "200 OK")) {
            alive = 1;
            break;
        }
    }

    pclose(fp);
    return alive;
}

void bind_url_to_function(const char *url) {
    const char *pong = check_url_alive(url) ? "URL is alive" : "URL is not alive";
    printf("%s\n", pong);
}

int main() {
    // Example usage
    const char *url = "http://example.com";
    bind_url_to_function(url);

    return 0;
}