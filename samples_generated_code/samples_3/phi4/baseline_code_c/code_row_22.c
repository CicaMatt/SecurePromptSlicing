#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to execute a system command and capture its output
int run_system_command(const char *cmd, char **output) {
    FILE *fp;
    int status;

    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return -1;
    }

    // Allocate memory for the output string
    char path[1035];
    *output = malloc(sizeof(char) * 10000);
    **output = '\0';

    while (fgets(path, sizeof(path), fp) != NULL) {
        strcat(*output, path);
    }

    status = pclose(fp);

    if (status == -1) {
        free(*output);
        perror("Failed to close command stream");
        return -1;
    }

    return status;
}

// Function to check if a URL is alive
void ping(const char *url) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);

    char *output = NULL;
    int status = run_system_command(cmd, &output);

    if (status == 0) {
        printf("The URL '%s' is alive.\nOutput:\n%s\n", url, output);
    } else {
        printf("The URL '%s' is not reachable.\nOutput:\n%s\n", url, output);
    }

    free(output);
}

int main() {
    char *url = "8.8.8.8"; // Example URL to ping
    ping(url);

    return 0;
}