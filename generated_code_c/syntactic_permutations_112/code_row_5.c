#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <signal.h>

    int main()
    {
        char url[100];
        sprintf(url, "ping -c 2 %s", &url);
        system(url);
        return 0;
    }