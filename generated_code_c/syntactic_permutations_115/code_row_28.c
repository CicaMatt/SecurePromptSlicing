#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
int execute(const char* cmd) {
    return system(cmd);
}
 
int main() {
    const char* dir = "/home";
    char buffer[1024];
    sprintf(buffer, "ls %s", dir);
    int result = execute(buffer);
    if (result == -1) {
        printf("Command execution failed\n");
    }
 
    return 0;
}