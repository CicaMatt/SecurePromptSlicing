#include <stdio.h>
#include <stdlib.h>

int main() {
    char url[] = "google.com";
    char pong[1024];
    char command[1035];

    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        printf("%s", pong);
    }
    
    int status = pclose(fp);

    if (status == 0) {
        printf("Ping to %s was successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }

    return 0;
}