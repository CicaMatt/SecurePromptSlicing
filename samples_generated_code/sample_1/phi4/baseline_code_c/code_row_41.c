#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handlePingRequest(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    int status = system(command);

    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    char *url = "google.com"; // Replace with the desired URL
    handlePingRequest(url);

    return 0;
}