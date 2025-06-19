//Importing libraries for file handling and writing.
#include<stdio.h>
#include<stdlib.h>

int main(){
//Declaring a pointer of type FILE and initializing it to NULL
FILE *fptr = NULL;

//Opening the file in write mode.
fptr = fopen("important_config", "w");

//Checking for errors
if(fptr == NULL){
printf("Unable to open/create file.");
return 1;
}

//Writing string into the file
fputs("important_config", fptr);

//Closing the file.
fclose(fptr);
return 0;
}