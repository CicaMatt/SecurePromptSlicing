#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "/ping";

void decorator(char (*func)(void)) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    char result[1024];
    strcpy(result, func());
    printf("%s", result);
}

char ping() {
    FILE *fp;
    char path[1024];

    fp = popen("ping -c 1 google.com", "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        // Only take the last line of ping output
    }
    pclose(fp);

    return url;
}

int main() {
    decorator(ping);
    return 0;
}