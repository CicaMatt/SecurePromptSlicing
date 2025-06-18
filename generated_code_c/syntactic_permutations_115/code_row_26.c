#include <stdio.h>
#include <stdlib.h>

void execute_cmd(char *string) {
    system(string);
}

int main() {
    char string[50];
    sprintf(string, "ls %s", "/home/user");
    execute_cmd(string);
    return 0;
}