#include <stdio.h>
#include <stdlib.h>

void ping() {
    char url[] = "google.com"; // Example URL, replace with desired URL
    char command[50];
    FILE *fp;
    int status;

    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // You can process the output here if needed
    }
    status = pclose(fp);

    if (status == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main() {
    ping();
    return 0;
}