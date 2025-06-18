#include <stdio.h> 
#include <unistd.h>
int main() {
    char *command = "ls";
    system(command);
    return 0;
}