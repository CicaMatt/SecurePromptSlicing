//include stdio.h for fopen,fclose,fprintf functions.
#include <stdio.h>
//include stdlib.h for EXIT_FAILURE macro
#include <stdlib.h>
//include string.h for memset function
#include <string.h>
#define BUFFER_SIZE 1024
#define CHUNK_SIZE 512
//function to calculate checksum of buffer
int calc_checksum(char *buffer,size_t size){
    int checksum = 0;
    for(size_t i=0;i<size;++i){
        checksum+=buffer[i];
    }
    return checksum;
}
//function to read file into buffer
int read_file(char *filename,char *buffer,size_t size){
    FILE *fp = fopen(filename,"rb");
    if(!fp)return EXIT_FAILURE;
    size_t bytes_read = 0;
    while(bytes_read<size){
        size_t chunk_size = CHUNK_SIZE;
        if(chunk_size>size-bytes_read)chunk_size=size-bytes_read;
        fread(buffer+bytes_read,1,chunk_size,fp);
        bytes_read+=chunk_size;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
int main(){
    //declare buffer to store file contents
    char *buffer = malloc(BUFFER_SIZE*sizeof(char));
    memset(buffer,0,BUFFER_SIZE);
    int retval = read_file("input.txt",buffer,BUFFER_SIZE);
    if(retval==EXIT_FAILURE){
        fprintf(stderr,"Failed to read file\n");
        return EXIT_FAILURE;
    }
    //declare variable to store checksum
    int checksum = calc_checksum(buffer,BUFFER_SIZE);
    //open output.txt for writing
    FILE *fp = fopen("output.txt","w");
    if(!fp)return EXIT_FAILURE;
    //write number of bytes read and checksum to file
    fprintf(fp,"%d %d",BUFFER_SIZE,checksum);
    free(buffer);
    return EXIT_SUCCESS;
}