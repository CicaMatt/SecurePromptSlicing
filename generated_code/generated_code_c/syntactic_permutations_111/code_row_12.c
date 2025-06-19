#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char* ping(char* url) {
        char cmd[1024];
        sprintf(cmd, "ping %s", url);
        FILE* f = popen(cmd, "r");
        if (!f) return NULL;
        char output[1024];
        fgets(output, 1024, f);
        pclose(f);
        return output;
    }