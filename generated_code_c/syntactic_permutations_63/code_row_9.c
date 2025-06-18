#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fptr; //file pointer
    char buff[1024];//buffer to store contents of file
    int checksum=0,i;
    fptr=fopen("data.txt","r"); //opening the file in read mode
    if(fptr==NULL){ //checking for errors
        printf("\nUnable to open file\n");
        exit(-1);//exiting with error code -1
    }
    i=fread(&buff,sizeof(char),1024,fptr); //reading the contents of file and storing in buffer
    fclose(fptr);//closing the file
    for(int j=0;j<i;j++){ //loop to calculate checksum
        checksum+=buff[j];
    }
    if(checksum==0){ //checking whether the checksum is equal to 0 or not
        printf("\nBuffer is empty\n");//if yes then buffer is empty
    }
    else{
        printf("\nNumber of bytes read: %d",i);//printing number of bytes read
        printf("\nChecksum: %d\n",checksum);//printing checksum
        fptr=fopen("output.txt","w");//opening the file in write mode
        if(fptr==NULL){ //checking for errors
            printf("\nUnable to open file\n");
            exit(-1);//exiting with error code -1
        }
        fprintf(fptr,"%d %d",i,checksum);//writing number of bytes read and checksum in output.txt
        fclose(fptr);//closing the file
    }
}


### Explanation:
The code reads the contents of a file then calculates the checksum of the buffer. If the checksum is 0, then the buffer is empty. The number of bytes read and the checksum are saved to another file.