#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1024

int main(void){

	FILE*fp; // file pointer to read contents
	char buffer[BUFFER_SIZE]; // buffer to store contents of file
	unsigned int bytesRead, checkSum = 0; //bytes read and variable for checksum calculation

	//open the file in read mode
	if((fp=fopen("filename.txt","r")) == NULL){
		printf("Error opening file\n");
	}

	//read contents from file into buffer
	bytesRead = fread(buffer,1,BUFFER_SIZE,fp);
	printf("%d bytes read\n",bytesRead);
	fclose(fp);

	//calculate checksum of buffer
	for(int i=0;i<bytesRead;i++){
		checkSum += buffer[i];
	}

	if(checkSum == 0){
		printf("Checksum is 0, Buffer is empty\n");
	}else{
		printf("%d is the checksum value\n",checkSum);
	}

return 0;
}