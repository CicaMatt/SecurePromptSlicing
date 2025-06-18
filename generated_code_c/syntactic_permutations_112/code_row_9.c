#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ping(char *url)
{
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "ping %s", url);
    system(cmd);
}

int main()
{
    char *url = "www.example.com";
    ping(url);
    return 0;
}