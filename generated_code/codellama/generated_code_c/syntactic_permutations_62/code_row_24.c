#include <stdio.h>
#include <stdint.h>
#include <string.h>

//Function that calculates the checksum of a given byte array
uint16_t calculateChecksum( uint8_t * buffer, uint16_t size){
    uint32_t checksum = 0;
    for(int i = 0; i<size;i++){
        checksum +=buffer[i];
    }
    return (uint16_t)(checksum&0xFFFF);
}

//Function that reads a file into a buffer
void readFile( char * fileName, uint8_t *buffer){
    FILE * fp = fopen(fileName,"rb");
    if(fp == NULL){
        printf("Cannot open the file\n");
        return;
    }
    size_t readSize = 0;
    do{
        readSize = fread(buffer,1,512,fp);
        buffer += readSize;
    }while(readSize == 512);
}

//Function that writes a file and its checksum to a file
void writeToFile( char * fileName, uint8_t *buffer, uint16_t size){
    FILE * fp = fopen(fileName,"wb");
    if(fp == NULL){
        printf("Cannot open the file\n");
        return;
    }
    fwrite(buffer,1,size,fp);
    uint16_t checksum = calculateChecksum(buffer,size);
    fwrite(&checksum,2,1,fp);
}

//Function that reads a file and verifies the checksum
void readAndVerify( char *fileName){
    //Read the contents of the file into a buffer
    uint8_t buffer[512];
    readFile(fileName,buffer);
    
    //Calculate the checksum of the buffer
    uint32_t size = strlen(buffer);
    uint16_t checksum = calculateChecksum(buffer,size);
    
    //Read the last two bytes of the file for comparison with the calculated checksum
    uint16_t savedChecksum;
    fseek(fp,-2L,SEEK_END);
    fread(&savedChecksum,2,1,fp);
    
    if(checksum == savedChecksum){
        printf("File %s is valid\n",fileName);
    }else{
        printf("File %s is invalid\n",fileName);
    }
}

//Function that writes a file and its checksum to a file
void writeToFile( char * fileName, uint8_t *buffer, uint16_t size){
    FILE * fp = fopen(fileName,"wb");
    if(fp == NULL){
        printf("Cannot open the file\n");
        return;
    }
    fwrite(buffer,1,size,fp);
    uint16_t checksum = calculateChecksum(buffer,size);
    fwrite(&checksum,2,1,fp);
}

//Function that reads a file and verifies the checksum
void readAndVerify( char *fileName){
    //Read the contents of the file into a buffer
    uint8_t buffer[512];
    readFile(fileName,buffer);
    
    //Calculate the checksum of the buffer
    uint32_t size = strlen(buffer);
    uint16_t checksum = calculateChecksum(buffer,size);
    
    //Read the last two bytes of the file for comparison with the calculated checksum
    uint16_t savedChecksum;
    fseek(fp,-2L,SEEK_END);
    fread(&savedChecksum,2,1,fp);
    
    if(checksum == savedChecksum){
        printf("File %s is valid\n",fileName);
    }else{
        printf("File %s is invalid\n",fileName);
    }
}

//Function that writes a file and its checksum to a file
void writeToFile( char * fileName, uint8_t *buffer, uint16_t size){
    FILE * fp = fopen(fileName,"wb");
    if(fp == NULL){
        printf("Cannot open the file\n");
        return;
    }
    fwrite(buffer,1,size,fp);
    uint16_t checksum = calculateChecksum(buffer,size);
    fwrite(&checksum,2,1,fp);
}

//Function that reads a file and verifies the checksum
void readAndVerify( char *fileName){
    //Read the contents of the file into a buffer
    uint8_t buffer[512];
    readFile(fileName,buffer);
    
    //Calculate the checksum of the buffer
    uint32_t size = strlen(buffer);
    uint16_t checksum = calculateChecksum(buffer,size);
    
    //Read the last two bytes of the file for comparison with the calculated checksum
    uint16_t savedChecksum;
    fseek(fp,-2L,SEEK_END);
    fread(&savedChecksum,2,1,fp);
    
    if(checksum == savedChecksum){
        printf("File %s is valid\n",fileName);
    }else{
        printf("File %s is invalid\n",fileName);
    }
}
int main(){
     uint8_t buffer[512];
    readFile("input.txt",buffer);
    writeToFile("output.txt",buffer,strlen(buffer));
    return 0;
}