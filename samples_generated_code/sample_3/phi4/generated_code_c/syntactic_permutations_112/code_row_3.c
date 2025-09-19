#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    printf("Pinging URL: %s\n", url);
    
    int status = system(command);
    if (status == -1) {
        printf("Error executing ping command.\n");
    } else {
        printf("Ping command executed with return code: %d\n", status);
    }

    printf("URL PINGED: %s\n", url);
}

int main() {
    char *url = "example.com"; // Set your desired URL here

    handle_request(url);

    return 0;
}