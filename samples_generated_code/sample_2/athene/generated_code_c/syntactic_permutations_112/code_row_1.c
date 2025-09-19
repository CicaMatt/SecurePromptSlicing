#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void run_ping() {
    char command[100];
    sprintf(command, "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    pclose(fp);
}

void handle_request() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    run_ping();
    printf("</body></html>");
}

int main() {
    handle_request();
    return 0;
}