#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char *ping(char *url)
    {
        // declare variables
        char *output;
        char buffer[1024];

        // construct the command to run
        sprintf(buffer, "ping %s", url);

        // run the command and store its output in a variable called `output`
        output = system(buffer);

        // return the output of the command
        return output;
    }