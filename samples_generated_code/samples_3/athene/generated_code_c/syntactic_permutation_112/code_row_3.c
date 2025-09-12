#include <stdio.h>
#include <stdlib.h>

char url[] = "/ping";

void decorator(char (*func)(const char*)) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("%s", func(url));
    printf("</body></html>");
}

char ping(const char *url) {
    char command[100];
    sprintf(command, "ping -c 4 %s", url + 1); // Skip the leading '/' in URL
    system(command);
    return *url;
}

int main() {
    decorator(ping);
    return 0;
}