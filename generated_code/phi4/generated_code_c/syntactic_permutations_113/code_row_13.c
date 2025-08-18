#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_url_alive(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    int result = system(command);

    if (result == 0) {
        printf("The URL '%s' is alive.\n", url);
    } else {
        printf("The URL '%s' is not alive.\n", url);
    }
}

int main() {
    char *url = "google.com"; // Change this to the desired URL
    check_url_alive(url);

    return 0;
}