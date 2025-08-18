#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "/ping"
#define BUFFER_SIZE 256

void ping(char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char result[BUFFER_SIZE];
    while(fgets(result, sizeof(result)-1, fp) != NULL) {
        printf("%s", result);
    }
    pclose(fp);
}

void handle_request(char *path, char *url) {
    if (strcmp(path, URL) == 0) {
        ping(url);
    } else {
        printf("Not found\n");
    }
}

int main() {
    char url[] = "example.com";
    handle_request(URL, url);
    return 0;
}