#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <unistd.h>

    char* url;
    int alive = 0;
    char *pong;

    void ping()
    {
        pong = malloc(sizeof(char) * 1024);
        if (system("ping -c 3 " + url) == 0)
            alive = 1;
        else
            alive = 0;
    }

    int main()
    {
        char* url = "http://example.com/";
        ping();
        return 0;
    }