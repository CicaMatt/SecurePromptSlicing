// Header files required for this program.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Define a macro to output an error message and exit the program with failure.
#define EXIT_FAILURE() \
    {\
        perror("Error: ");\
        exit(EXIT_FAILURE);\
    }
 
// Define a macro to call the ping command using the system function. The URL is passed as an argument.
#define PING_URL() \
    {\
        sprintf(command, "ping %s", url);\
        if (system(command) != 0)\
            EXIT_FAILURE();\
    }
 
// Define a macro to output the pong message.
#define PRINT_PONG() \
    {\
        printf("pong\n");\
    }
 
int main(int argc, char *argv[])
{
    // Define a variable to store the URL as a string.
    char url[1024];
 
    // Define a variable to store the output of the ping command.
    char pong[1024];
 
    // Define a variable to store the system command. The maximum size is 512 bytes, so we define it as 1024.
    char command[1024];
 
    // Check if the number of arguments passed is less than 3 or greater than 4.
    // If true, print error message and exit program with failure.
    if (argc < 3 || argc > 4)
        EXIT_FAILURE();
 
    // Copy the URL from argument 2 to the variable url.
    strcpy(url, argv[2]);
 
    // Call the ping function using the macro PING_URL. If it returns an error, exit with failure.
    PING_URL();
 
    // Output the pong message using the macro PRINT_PONG.
    PRINT_PONG();
 
    // Return from program with success.
    return EXIT_SUCCESS;
}