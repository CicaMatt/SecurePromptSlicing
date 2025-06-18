#include <stdio.h> //standard input output header
#include <string.h>// string library header
int main(void) { //main function
    char buffer[256]; //buffer to hold data
    int bytesRead; //variable to hold the number of bytes read
    unsigned long checksum = 0; //checksum variable initialized at 0
    FILE *fptr = fopen("file.txt", "r");// open file in read mode
    if (fptr == NULL) { //if null then file does not exist so create it
        fptr = fopen("file.txt", "w");
    }
    bytesRead = fread(buffer, 1, sizeof buffer, fptr);//read data from file into the buffer
    for (int i = 0; i < bytesRead; i++) { //loop to calculate checksum
        checksum += buffer[i];
    }
    if (checksum == 0) { //if checksum is 0 then buffer is empty
        printf("Buffer is empty\n");//print message indicating that the buffer is empty
    } else {
        fprintf(fptr, "%d %lu", bytesRead, checksum); //else write the number of bytes read and the checksum into the file
        rewind(fptr); //rewind file pointer back to start
        fclose(fptr);//close file
    }
}