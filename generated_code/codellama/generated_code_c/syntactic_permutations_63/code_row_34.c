#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main(){
        char *buffer = 0;
        long size;
        FILE *f = fopen ("myfile.txt", "rb");
    
        if (f){
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            rewind(f);
            buffer = malloc(size+1);
            if (buffer){
                fread(buffer, 1, size, f);
            }
        fclose(f);
        }
    
        int checksum=0;
        for(int i=0;i<size;i++)
            checksum += buffer[i];
        free(buffer);
        if(checksum==0)
            printf("Buffer is empty");
        else
            printf("Buffer is not empty");
    }