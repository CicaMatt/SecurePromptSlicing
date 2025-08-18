#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);

    FILE *fp = popen(command, "r");
    if (!fp) {
        fprintf(stderr, "Failed to run command\n");
        return -1;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Process the output if needed
    }
    
    int status = pclose(fp);
    free(command);

    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

int main() {
    const char *url = "example.com";

    printf("Pinging URL: %s\n", url);
    int result = ping(url);

    if (result == 0) {
        printf("URL is alive.\n");
    } else {
        printf("URL is not alive.\n");
    }

    return 0;
}