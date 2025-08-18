#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_url_status(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int status = system(command);
    return status == 0;
}

int main() {
    const char *url = "example.com";
    int is_alive = check_url_status(url);

    if (is_alive) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }

    return 0;
}