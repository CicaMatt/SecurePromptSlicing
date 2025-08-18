#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[256] = "example.com";

void bindFunctionToURL(const char* url) {
    if (strcmp(url, "ping") == 0) {
        char command[512];
        snprintf(command, sizeof(command), "ping -c 4 %s", this_url);
        FILE *fp;
        
        fp = popen(command, "r");
        if (!fp) {
            perror("Failed to run ping");
            return;
        }
        
        char pong[1024] = {0};
        while (fgets(pong, sizeof(pong), fp) != NULL) {
            printf("%s", pong);
        }

        int status = pclose(fp);
        if (status == 0) {
            printf("Ping command succeeded.\n");
        } else {
            fprintf(stderr, "Ping command failed with status %d.\n", status);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    strcpy(url, argv[1]);
    
    bindFunctionToURL("ping");
    
    return 0;
}