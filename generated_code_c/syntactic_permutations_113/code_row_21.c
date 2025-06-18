#include <stdio.h>
    int ping(char *url) {
        char pong[512] = "";
        char command[7 + strlen(url)] = "ping ";
        strcat(command, url);
        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            printf("Failed to run command\n" );
            return 1;
        }
        while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
            ;
        }
        int status = pclose(fp);
        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            return 0;
        } else {
            return 1;
        }
    }