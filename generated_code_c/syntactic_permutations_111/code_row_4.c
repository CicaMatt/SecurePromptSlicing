// include the libraries needed to run this code
#include<stdio.h>
#include<string.h>

// define the function "ping()"
void ping(char* url) {
    // create a variable called output that stores the output of the command "ping"
    char* output = system("ping", url);
    
    // return the output of the command "ping"
    return output;
}