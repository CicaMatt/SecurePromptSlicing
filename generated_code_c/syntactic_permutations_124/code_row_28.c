#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: please input a string\n");
        return 1;
    }
    char* input = trimwhitespace(argv[1]);
    printf("%s\n",input);
    free(input);
    return 0;
}
char* trimwhitespace(char *str)
{
    // Trim leading space
    while(isspace(*str)) str++;
    
    if(*str == 0)  // All spaces?
        return str;
    
    // Trim trailing space
    char *end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    
    // Write new null terminator character
    end[1] = '\0';
    return str;
}