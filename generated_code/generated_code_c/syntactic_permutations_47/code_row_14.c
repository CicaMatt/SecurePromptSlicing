#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    int main(int argc, char *argv[])
    {
        FILE *file;
        file = fopen("example.jpg", "r");
        if (file == NULL)
            printf("File does not exist\n");
        else
        {
            printf("File exists\n");
        }
        return 0;
    }