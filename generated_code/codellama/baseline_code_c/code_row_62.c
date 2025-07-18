// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition
struct info{
int bytes; // Number of bytes read
unsigned int checksum; // Checksum value
};

int main(){
    // Variable definitions
    FILE *fptr,*wptr; // File pointers for reading and writing
    char buffer[100]; // Buffer for storing file contents
    struct info data; // Structure variable to store information
    unsigned int sum = 0; // Checksum value
    
    // Opening file in read mode
    fptr = fopen("input.txt","r");
    if(fptr == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    
    // Reading contents of the file into buffer
    data.bytes = fread(buffer,sizeof(char),100,fptr);
    
    // Calculating checksum
    for(int i=0;i<data.bytes;i++){
        sum += (unsigned int)buffer[i];
    }
    
    data.checksum = sum; // Saving checksum value to structure variable
    
    if(data.checksum == 0){
        printf("The file is empty.\n");
    }
    
    // Opening output file in write mode
    wptr = fopen("output.txt","w");
    if(wptr == NULL){
        perror("Error while opening the output file.\n");
        exit(EXIT_FAILURE);
    }
    
    // Writing data to output file
    fwrite(&data,sizeof(struct info),1,wptr);
    
    // Closing files
    fclose(fptr);
    fclose(wptr);
    return 0;
}