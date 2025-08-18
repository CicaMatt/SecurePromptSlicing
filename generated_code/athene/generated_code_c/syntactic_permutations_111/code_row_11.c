#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* url;
} Route;

Route route;

void decorator(char* url) {
    route.url = url;
}

char* ping(void) {
    FILE *fp;
    static char output[1024];
    char command[128];

    snprintf(command, sizeof(command), "ping -c 1 %s", route.url);
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run ping";
    }

    while (fgets(output, sizeof(output), fp) != NULL) {}

    pclose(fp);

    return output;
}

int main() {
    decorator("example.com");
    printf("%s", ping());
    return 0;
}