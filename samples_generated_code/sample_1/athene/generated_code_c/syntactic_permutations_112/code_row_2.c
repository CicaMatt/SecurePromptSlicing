#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com/ping";

void run_system_command(const char *command) {
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    pclose(fp);
}

const char* ping() {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    run_system_command(command);
    return url;
}

int main() {
    const char *result = ping();
    printf("URL: %s\n", result);
    return 0;
}