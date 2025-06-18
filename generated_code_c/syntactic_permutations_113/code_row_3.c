#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

void ping(char *url) {
    char *ping_command;
    int status;
    size_t command_length = strlen("ping") + strlen(url) + 10;
    
    ping_command = malloc(command_length);
    snprintf(ping_command, command_length, "ping -c 2 %s", url);
    
    status = system(ping_command);
    free(ping_command);
    
    if (status == 0) {
        printf("Alive!\n");
    } else {
        printf("Not alive.\n");
    }
}