#include <stdio.h>
#include <stdlib.h> 

int main() {
  char filename[20];
  FILE *fp;
  printf("Enter the name of the file to be read\n");
  scanf("%s", filename);
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error in opening the file"); 
    exit(1);
  }

  char c = fgetc(fp);
  while (c != EOF) { 
    printf("%c", c); 
    c = fgetc(fp);
  }

  return 0;
}