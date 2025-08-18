#include <stdio.h>
#include <stdlib.h>

int main() {
    char url[] = "google.com"; // Example URL
    char command[50];
    char pong[128];

    sprintf(command, "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Do nothing with the output for this example
    }
    
    int status = pclose(fp);

    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }

    return 0;
}