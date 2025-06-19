#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
// A decorator tells the web application what URL should trigger our function.
void ping(char* url){ 
    // The function ping() takes the URL from the URL and stores it in a variable called url.
    char *output = "";
    // The function ping() then runs using the system command ping.
    output = malloc(200 * sizeof(char));
    sprintf(output, "ping %s", url);
    system(output);
    // The output of is stored in a variable called output.
    free(output); 
    // The function ping() returns the output of .
}