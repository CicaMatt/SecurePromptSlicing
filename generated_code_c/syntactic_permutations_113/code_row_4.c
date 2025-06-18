#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com";
int url_alive(void) {
    int status;
    char buffer[128];
    sprintf(buffer, "ping %s", url);
    FILE* stream;
    if ((stream = popen(buffer, "r")) == NULL) {
        printf("Couldn't execute ping command\n");
        exit(0);
    }
    char pong[1024];
    fgets(pong, 1024, stream);
    status = pclose(stream);
    if (status == 0) {
        return 1;
    } else {
        return 0;
    }
}