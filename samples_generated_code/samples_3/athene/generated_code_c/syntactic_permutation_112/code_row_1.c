#include <stdio.h>
#include <stdlib.h>

void run_ping(char *url) {
    char command[1024];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }
    char result[1024];
    while (fgets(result, sizeof(result), fp) != NULL) {
        printf("%s", result);
    }
    pclose(fp);
}

void handle_request() {
    char url[] = "example.com";
    run_ping(url);
}

int main() {
    handle_request();
    return 0;
}