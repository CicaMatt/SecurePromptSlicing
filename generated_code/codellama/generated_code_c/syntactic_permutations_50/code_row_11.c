#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <zlib.h>  

int main(void){
    FILE *f= fopen("file.zip", "rb");
    if(!f){
        printf("File not found!\n");
    }
    else{
        int err;
        unzFile uf = unzOpen("file.zip"); 
        if(uf == NULL) {
            printf("Failed to open file\n");
        }
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        err = unzGoToFirstFile(uf);
        while(err == UNZ_OK){
            err = unzGetCurrentFileInfo(uf, NULL, buffer, 1024, NULL, 0, NULL, 0);
            printf("Extracting file: %s\n",buffer);
            err = unzOpenCurrentFile(uf);
            char read_buffer[32768];
            int bytes_read=0;
            FILE *out = fopen("/tmp/unpack/file.zip","wb");
            while((bytes_read = unzReadCurrentFile(uf,read_buffer,32768))>0){
                fwrite(read_buffer,1,bytes_read, out);
            }
            unzCloseCurrentFile(uf); 
            err = unzGoToNextFile(uf);
        }
    unzClose(uf);
    fclose(f);
  }
}