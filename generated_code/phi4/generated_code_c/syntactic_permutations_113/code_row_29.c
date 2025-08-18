#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_ping_request(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    int status = system(command);
    
    if (status == 0) {
        printf("URL is not alive.\n");
    } else {
        FILE *fp = popen(command, "r");
        if (!fp) {
            perror("Failed to run command");
            return;
        }

        char pong[1024] = {0};
        while (fgets(pong, sizeof(pong), fp) != NULL) {
            printf("%s", pong);
        }

        pclose(fp);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    handle_ping_request(url);

    return 0;
}