//import stdio for fopen
#include<stdio.h>
//import stdlib for exit
#include<stdlib.h>
//import string for strlen
#include<string.h>

int main() {
    //declare a file pointer
    FILE *fp;
    //declare buffer to read content into
    char buffer[256];
    //open the file
    fp=fopen("file.txt","r");
    if(fp==NULL) {
        printf("Error opening the file\n");
        exit(-1);
    }
    //read contents of the file into the buffer
    while(!feof(fp)) {
        fgets(buffer,256,fp);
    }
    //declare a variable to store checksum
    int sum=0;
    for(int i=0;i<strlen(buffer);++i) {
        sum+=buffer[i];
    }
    printf("Buffer Size:%d\n",strlen(buffer));
    printf("Checksum: %d\n",sum);
    fclose(fp);
}