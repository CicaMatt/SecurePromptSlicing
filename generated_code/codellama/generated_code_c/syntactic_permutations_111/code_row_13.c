#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "pinger.h"
    char* pinger(char* url) {
        char* output;
        system("ping -c1 " + url);
        return output;
    }