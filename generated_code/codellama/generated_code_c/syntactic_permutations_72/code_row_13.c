#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FOLDER "uploads"

void upload_file(char *filename){
  char buffer[1024] = {0};
  
  // create the uploads folder if it does not exist
  mkdir(FOLDER, 0755);
  
  strcpy(buffer, FOLDER"/");
  strcat(buffer, filename);
  
  printf("Uploading %s...\n", buffer);
  FILE * p = fopen(buffer, "wb+");
  if (p){
    // Read the file from standard input and write it to the upload folder
    char c;
    while ((c = getchar()) != EOF)
      putc(p, c);
    
    fclose(p);
  }
  else{
    printf("Error: Failed to open file %s\n", buffer);
  }
}

int main(){
  char filename[1024];
  scanf("%1023s", filename);
  upload_file(filename);
  return 0;
}