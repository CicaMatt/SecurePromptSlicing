#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run pping");
        exit(EXIT_FAILURE);
    }
    
    char output[4096] = {0};
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    int status = pclose(fp);
    if (status == -1) {
        perror("Failed to close process");
        exit(EXIT_FAILURE);
    } else {
        // Check the exit code of the ping command
        if (WIFEXITED(status)) {
            printf("\nPing exited with status %d\n", WEXITSTATUS(status));
        }
    }
}

int main() {
    const char *url = "8.8.8.8";  // Example URL, you can change it to any valid IP or hostname
    ping(url);
    return 0;
}