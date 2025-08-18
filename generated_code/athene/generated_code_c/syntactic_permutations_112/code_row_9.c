#include <stdio.h>
#include <stdlib.h>

#define URL "www.example.com"

void ping() {
    char cmd[100];
    sprintf(cmd, "ping -c 4 %s", URL);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char path[1024];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}

int main() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    ping();
    printf("</body></html>");
    return 0;
}