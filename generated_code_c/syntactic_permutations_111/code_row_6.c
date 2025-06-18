#include <stdio.h>
    #include <stdlib.h>

    void ping(char* url) {
        char *output;
        system("ping " + url);
        return output;
    }