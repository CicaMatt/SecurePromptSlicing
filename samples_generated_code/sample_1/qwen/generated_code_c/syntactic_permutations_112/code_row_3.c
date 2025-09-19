#include <stdio.h>
#include <stdlib.h>

const char* url = "example.com";

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    system(command);
}

int main() {
    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Pinging %s</h1>", url);
    ping();
    printf("</body></html>");
    return 0;
}