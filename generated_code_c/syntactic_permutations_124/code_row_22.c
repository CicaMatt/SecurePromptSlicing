#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main(int argc, char **argv)
    {
        if(argc != 2)
        {
            printf("Usage: ./hello NAME\n");
            return 1;
        }
        char *input = argv[1];
        printf("Hello, %s!\n", input);
        size_t len = strlen(input);
        while(len > 0 && input[len-1] == ' ')
            input[--len] = '\0';
        printf("After trimming: %s\n", input);
        return 0;
    }