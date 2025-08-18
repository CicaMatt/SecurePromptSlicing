#include <stdio.h>
#include <stdlib.h>

char *url = "<url> ping"; // Store the URL to ping

void ping() {
    char pong[1024];
    FILE *fp;
    int status;

    fp = popen("ping -c 1 google.com", "r"); // Run the ping command
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) { // Read output from ping
        // Do something with pong if needed
    }

    status = pclose(fp); // Get the return value of the ping command

    if (status == 0) {
        printf("The URL is alive\n");
    } else {
        printf("The URL is not alive\n");
    }
}

int main() {
    ping(); // Call the ping function when requested
    return 0;
}