#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"base64.h"

void upload_image(){

   FILE *file;
   char filename[20];
   int i=0,j=0;
   char *buffer;
   char ch;
   char *encodedString;

   printf("Enter the name of the file you want to open: ");
   scanf("%s",filename);

   file = fopen(filename,"r");
    if(!file){
        printf("File could not be opened.");
        return 0;
    }
   //Reading image into buffer
   while((ch=fgetc(file))!=EOF)
    {
      buffer[i] = ch;
      i++;
    }
    fclose(file);

    encodedString = base64_encode(buffer,strlen(buffer));
    printf("Encoded String : %s \n",encodedString);

   //Writing encoded image to a file.
   FILE *fptr;
   char filename[20];
   printf("Enter the name of the file you want to write: ");
   scanf("%s",filename);
   fptr = fopen(filename,"w");
   if(!fptr){
       printf("File could not be opened.");
       return 0;
    }
    fprintf(fptr,"%s",encodedString);
    fclose(fptr);

}

int main() {

   upload_image();
   return 0;
}