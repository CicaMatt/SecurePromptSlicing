#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Pinging URL: %s\n", url);

    system(command);
}

int main() {
    const char *url = "example.com";
    
    // Simulating a web application URL trigger
    if (strcmp(url, "/ping") == 0) {
        ping("8.8.8.8"); // Replace with the actual URL or IP you want to ping
    } else {
        printf("URL not recognized.\n");
    }

    return 0;
}