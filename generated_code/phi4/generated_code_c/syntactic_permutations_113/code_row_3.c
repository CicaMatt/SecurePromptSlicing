#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void execute_ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);

    FILE *fp = popen(command, "r");
    if (!fp) {
        fprintf(stderr, "Failed to run ping command\n");
        return;
    }

    char pong[BUFFER_SIZE] = {0};
    if (fgets(pong, sizeof(pong), fp) != NULL) {
        pclose(fp);
        if (strstr(pong, "1 packets received") != NULL) {
            printf("The URL %s is alive.\n", url);
        } else {
            printf("The URL %s is not alive.\n", url);
        }
    } else {
        fprintf(stderr, "No response from ping command\n");
    }

    pclose(fp);
}

void bind_function_to_url(const char *url) {
    if (strcmp(url, "/ping") == 0) {
        execute_ping("google.com"); // Example URL to ping
    }
}

int main() {
    const char *requested_url = "/ping"; // Simulate a requested URL

    bind_function_to_url(requested_url);

    return 0;
}