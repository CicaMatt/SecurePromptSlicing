#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *url = "<url>";
char pong[1024];

int check_url_alive(const char *url) {
    char command[512];
    snprintf(command, sizeof(command), "curl -I %s > /dev/null 2>&1", url);
    int status = system(command);
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

void bind_function_to_url() {
    if (check_url_alive(url)) {
        strcpy(pong, "URL is alive");
    } else {
        strcpy(pong, "URL is not alive");
    }
    printf("%s\n", pong);
}

int main() {
    bind_function_to_url();
    return 0;
}