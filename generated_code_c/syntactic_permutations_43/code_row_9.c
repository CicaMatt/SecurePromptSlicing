//Import necessary libraries.
#include <stdio.h>
#include <stdlib.h>

int main() {
  //Declare variables and set them to NULL.
  FILE *fp;
  int ch = '\0';
  const char *filename = "file.txt";

  //Open the file in read mode.
  fp = fopen(filename, "r");

  //Check if file exists and is readable.
  if (fp == NULL) {
    printf("Error: Failed to open %s\n", filename);
    exit(1);
  }

  //Read the contents of the file character by character and print them.
  while ((ch = fgetc(fp)) != EOF)
    printf("%c", ch);

  //Close the file when done.
  fclose(fp);

  return 0;
}