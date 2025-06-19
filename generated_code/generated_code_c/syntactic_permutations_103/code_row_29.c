#include<stdio.h>
    #include<fcntl.h>
    #include<sys/types.h>
    #include<stdlib.h> 
    int main(int argc, char const *argv[])
    {
        int file_desc;
        char *file_name = "test.txt";
        if ((file_desc = open(file_name, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644)) < 0)
        {
            printf("Error creating file");
        }

        return EXIT_SUCCESS;
    }