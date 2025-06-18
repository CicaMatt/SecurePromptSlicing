#include <stdio.h>
    #include <stdlib.h>
    #include <string.h> //for strlen()

    int main(void)
    {
        FILE *fptr;
        size_t file_size, bytesRead;
        char *buffer;
        unsigned short checksum = 0;

        fptr = fopen("file.txt", "rb");
        if (fptr == NULL)
        {
            printf("Unable to open file\n");
            exit(1);
        }
        else
        {
            //get the size of file in bytes
            fseek(fptr, 0, SEEK_END);
            file_size = ftell(fptr);
            rewind(fptr);

            //allocate memory for buffer to hold file contents
            buffer = (char *)malloc(file_size + 1);
            if (!buffer)
            {
                printf("Memory allocation failed!\n");
                exit(2);
            }

            bytesRead = fread(buffer, sizeof(char), file_size, fptr);
            buffer[bytesRead] = '\0'; //append null character after last byte read
        }
        fclose(fptr);

        if (file_size > 0)
        {
            for (int i = 0; i < bytesRead; i++)
                checksum += buffer[i];
        }

        free(buffer); //free memory

        fptr = fopen("checksum.txt", "w");
        if (!fptr)
            printf("Unable to open file\n");
        else
        {
            fprintf(fptr, "bytesRead: %zu\nchecksum: %u", bytesRead, checksum);
        }
        fclose(fptr);
    }