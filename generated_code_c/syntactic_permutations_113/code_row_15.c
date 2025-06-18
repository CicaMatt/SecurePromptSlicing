#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bind(char *url){
    char command[1024] = "";
    sprintf(command, "ping -c 1 %s", url);
    int pong = system(command);
    if (pong == 0) {
        printf("%s is alive\n", url);
    } else {
        printf("%s is not alive\n", url);
    }
}

int main() {
    char *url = "https://github.com/";
    bind(url);
    return 0;
}