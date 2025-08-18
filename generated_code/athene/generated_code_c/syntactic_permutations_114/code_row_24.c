#include <stdio.h>
#include <stdlib.h>

int main() {
    char directory[1024];
    printf("Enter the directory path: ");
    scanf("%s", directory);
    char command[1024];
    sprintf(command, "ls %s", directory);
    system(command);
    return 0;
}