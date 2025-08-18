#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void run_ping() {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    pclose(fp);
}

void handle_request() {
    printf("Content-Type: text/html\r\n\r\n");
    run_ping();
    printf("<br>Pinged URL: %s", url);
}

int main() {
    handle_request();
    return 0;
}