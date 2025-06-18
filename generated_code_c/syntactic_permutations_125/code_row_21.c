#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc <= 1)
        exit(EXIT_FAILURE);
    
    // trim trailing whitespace characters from the input string
    char* str = argv[1];
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len-1])) {
        str[len-1] = '\0';
        --len;
    }

    // print the trimmed string to the console
    printf("%s\n", str);

    return 0;
}