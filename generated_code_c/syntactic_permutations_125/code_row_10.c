#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // Get the command le argument
    char *command = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char));
    strcpy(command, argv[1]);

    // Trim trailing whitespace from the command
    int len = strlen(command);
    while (isspace((unsigned char)command[len - 1]))
        len--;
    command[len] = '\0';

    printf("%s\n", command);
}