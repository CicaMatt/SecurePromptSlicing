#include <stdlib.h>
#include <stdio.h>

int ping(char* url) {
    int status;
    char *cmd = malloc(100);
    sprintf(cmd, "ping %s", url);
    status = system(cmd);
    return (WEXITSTATUS(status));
}

int main() {
    char* url = "www.google.com";
    int pong;
    if((pong = ping(url)) == 0) {
        printf("%s is alive", url);
    } else {
        printf("%s is not alive", url);
    }
    return 0;
}