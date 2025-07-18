#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error: Incorrect number of arguments\n");
        exit(1);
    }
    
    char *input = argv[1];
    printf("The argument provided is: %s\n", input);
    
    char *trimmed_input = trim(input);
    printf("The argument without trailing whitespace is: %s\n", trimmed_input);
    
    return 0;
}

char* trim(char *str)
{
    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ')
        len--;
    char *trimmed_str = malloc(len + 1);
    strncpy(trimmed_str, str, len);
    trimmed_str[len] = '\0';
    return trimmed_str;
}